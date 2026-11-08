// Copyright 2026 mrazakam

#include "gui/components/features/Protocol.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gui/Server.hpp"
#include "gui/components/basic/Button.hpp"
#include "gui/components/basic/Group.hpp"
#include "gui/components/basic/Input.hpp"
#include "gui/components/basic/Line.hpp"
#include "gui/components/basic/Text.hpp"
#include "gui/components/features/TAPInterfaceHelpers.hpp"

using std::cout;
using std::endl;
using std::getline;
using std::istringstream;
using std::lround;
using std::string;
using std::vector;
using TAPUI::add_text;
using TAPUI::blue;
using TAPUI::blue_light;
using TAPUI::border;
using TAPUI::create_panel;
using TAPUI::muted;
using TAPUI::panel_dark;
using TAPUI::row_border;
using TAPUI::text_color;

namespace {
const size_t max_protocol_lines = 25;
}

void Protocol::log_protocol(string log) {
  vector<string> wrapped_lines;
  istringstream response_stream(log);
  string source_line;
  string current_line;
  const int available_width = width - px(32);

  auto append_word = [&](const string& word) {
    string candidate = current_line.empty() ? word : current_line + " " + word;
    log_entries.front()->text = candidate;
    if (log_entries.front()->measureWidth() <= available_width) {
      current_line = candidate;
      return;
    }

    if (!current_line.empty()) {
      wrapped_lines.push_back(current_line);
      current_line.clear();
    }

    for (size_t byte_index = 0; byte_index < word.size();) {
      const unsigned char first_byte =
          static_cast<unsigned char>(word[byte_index]);
      size_t character_length = 1;
      if ((first_byte & 0xe0) == 0xc0)
        character_length = 2;
      else if ((first_byte & 0xf0) == 0xe0)
        character_length = 3;
      else if ((first_byte & 0xf8) == 0xf0)
        character_length = 4;

      const string character = word.substr(byte_index, character_length);
      candidate = current_line + character;
      log_entries.front()->text = candidate;
      if (!current_line.empty() &&
          log_entries.front()->measureWidth() > available_width) {
        wrapped_lines.push_back(current_line);
        current_line = character;
      } else {
        current_line = candidate;
      }
      byte_index += character_length;
    }
  };

  while (getline(response_stream, source_line)) {
    if (!source_line.empty() && source_line.back() == '\r')
      source_line.pop_back();
    istringstream words(source_line);
    string word;
    while (words >> word) append_word(word);
    if (!current_line.empty()) {
      wrapped_lines.push_back(current_line);
      current_line.clear();
    }
  }

  if (wrapped_lines.empty()) wrapped_lines.push_back("(empty response)");
  if (wrapped_lines.size() > max_protocol_lines) {
    wrapped_lines.erase(wrapped_lines.begin(),
                        wrapped_lines.end() - max_protocol_lines);
    wrapped_lines.front() = "... (response truncated)";
  }

  response_lines.insert(response_lines.end(), wrapped_lines.begin(),
                        wrapped_lines.end());
  response_ends.push_back(response_lines.size());
  if (response_lines.size() > max_protocol_lines) {
    const size_t removed_lines = response_lines.size() - max_protocol_lines;
    response_lines.erase(response_lines.begin(),
                         response_lines.begin() + removed_lines);

    vector<size_t> visible_response_ends;
    for (size_t end : response_ends) {
      if (end > removed_lines)
        visible_response_ends.push_back(end - removed_lines);
    }
    response_ends.swap(visible_response_ends);
  }

  for (size_t index = 0; index < log_entries.size(); ++index)
    log_entries[index]->text =
        index < response_lines.size() ? response_lines[index] : "";

  for (Line* separator : response_separators) separator->color.a = 0;
  for (size_t end : response_ends) {
    if (end > 0 && end <= response_separators.size())
      response_separators[end - 1]->color = row_border;
  }
}

void Protocol::submit_command() {
  string response = this->server->request(this->protocol_command);
  cout << response << endl;
  this->log_protocol(response);
}

Protocol::Protocol(App* app, int x, int width, int panel_height, float scale,
                   std::string& protocol_command, bool& command_focused,
                   Server* server)
    : Component(app, x, 0),
      panel(nullptr),
      protocol_command(protocol_command),
      command_focused(command_focused),
      server(server),
      width(width) {
  px = [scale](float value) { return static_cast<int>(lround(value * scale)); };
  Group* protocol = create_panel(app, width, panel_height, "03 / PROTOCOL LOG");

  for (size_t index = 0; index < max_protocol_lines; ++index) {
    const string line =
        index < response_lines.size() ? response_lines[index] : "";
    log_entries.push_back(add_text(protocol, app, px(16), px(55 + index * 24),
                                   line, px(11), text_color));
    SDL_Color separator_color = row_border;
    separator_color.a = 0;
    Line* separator = new Line(app, px(16), px(75 + index * 24), width - px(16),
                               px(75 + index * 24), separator_color);
    response_separators.push_back(separator);
    protocol->children.push_back(separator);
  }

  const int command_y = px(684);
  Input* command_input = new Input(
      app, px(16), command_y, width - px(112), px(36), &protocol_command,
      &command_focused, panel_dark, text_color, 0, {37, 70, 107, 255},
      "Enter protocol command...", "", 0, px(12), {97, 120, 149, 255});
  protocol->children.push_back(command_input);
  protocol->children.push_back(new Button(
      app, width - px(88), command_y, px(72), px(36), "EXECUTE",
      [this]() { this->submit_command(); }, {11, 26, 46, 255}, blue_light, 0,
      {37, 70, 107, 255}, {16, 39, 68, 255}, {11, 26, 46, 255}, 10, 1, true));
  panel = protocol;
}

void Protocol::render(int origin_x, int origin_y) {
  panel->render(origin_x + x, origin_y + y);
}

Protocol::~Protocol() { delete panel; }
