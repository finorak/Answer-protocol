// Copyright 2026 mrazakam

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "gui/Server.hpp"
#include "gui/json.hpp"
#include "gui/components/basic/Button.hpp"
#include "gui/components/basic/Group.hpp"
#include "gui/components/basic/ScrollableGroup.hpp"
#include "gui/components/basic/Text.hpp"
#include "gui/components/features/Environment.hpp"
#include "gui/components/features/TAPInterfaceHelpers.hpp"

using std::getline;
using std::isspace;
using std::istringstream;
using std::string;
using std::vector;
using json = nlohmann::json;
using TAPUI::add_chat_line;
using TAPUI::add_row_rule;
using TAPUI::add_text;
using TAPUI::blue;
using TAPUI::blue_light;
using TAPUI::border;
using TAPUI::muted;
using TAPUI::panel_dark;
using TAPUI::text_color;

namespace {
vector<string> wrap_text(Text& measure, const string& text, int max_width) {
  vector<string> lines;
  string line;
  string word;

  auto append_word = [&](const string& value) {
    if (!line.empty()) {
      measure.text = line + " " + value;
      if (measure.measureWidth() <= max_width) {
        line = measure.text;
        return;
      }
      lines.push_back(line);
      line.clear();
    }

    measure.text = value;
    if (measure.measureWidth() <= max_width) {
      line = value;
      return;
    }

    string chunk;
    for (size_t offset = 0; offset < value.size();) {
      const unsigned char first = static_cast<unsigned char>(value[offset]);
      size_t length = 1;
      if ((first & 0xe0) == 0xc0)
        length = 2;
      else if ((first & 0xf0) == 0xe0)
        length = 3;
      else if ((first & 0xf8) == 0xf0)
        length = 4;

      const string character = value.substr(offset, length);
      measure.text = chunk + character;
      if (!chunk.empty() && measure.measureWidth() > max_width) {
        lines.push_back(chunk);
        chunk = character;
      } else {
        chunk += character;
      }
      offset += length;
    }
    line = chunk;
  };

  for (size_t offset = 0; offset < text.size();) {
    const unsigned char character = static_cast<unsigned char>(text[offset]);
    if (isspace(character)) {
      if (!word.empty()) {
        append_word(word);
        word.clear();
      }
      ++offset;
      continue;
    }

    size_t length = 1;
    if ((character & 0xe0) == 0xc0)
      length = 2;
    else if ((character & 0xf0) == 0xe0)
      length = 3;
    else if ((character & 0xf8) == 0xf0)
      length = 4;
    word.append(text, offset, length);
    offset += length;
  }

  if (!word.empty()) append_word(word);
  if (!line.empty()) lines.push_back(line);
  return lines;
}
}  // namespace

void Environment::show_npcs() {
  for (Component* component : npc_components->children) delete component;

  npc_components->children.clear();

  int index = 0;
  for (const string& npc : npcs) {
    const int y = px(5 + index * 38);
    add_text(npc_components, app, px(16), y, "NPC", px(10), blue_light, px(1));
    add_text(npc_components, app, px(64), y, npc, px(11), text_color);

    npc_components->children.push_back(new Button(
        app, width - px(196), y - px(5), px(52), px(24), "TALK",
        [this, npc]() { log_protocol(server->request("TALK " + npc)); },
        {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
        {11, 26, 46, 255}, 10, 1, true));

    npc_components->children.push_back(new Button(
        app, width - px(137), y - px(5), px(66), px(24), "ATTACK",
        [this, npc]() {
          log_protocol(server->request("ATTACK " + npc));
          this->update_hp();
        },
        {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
        {11, 26, 46, 255}, 10, 1, true));

    npc_components->children.push_back(new Button(
        app, width - px(64), y - px(5), px(52), px(24), "QUEST",
        [this, npc]() { log_protocol(server->request("QUEST " + npc)); },
        {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
        {11, 26, 46, 255}, 10, 1, true));

    add_row_rule(npc_components, app, px(16), y + px(27), width - px(16));
    ++index;
  }
  npc_components->setContentHeight(px(5 + index * 38));
}

void Environment::show_players() {
  for (Component* component : player_components->children) delete component;

  player_components->children.clear();

  string names;
  for (const string& player : players) {
    if (!names.empty()) names += ", ";
    names += player;
  }

  Text measure(app, 0, 0, "", px(11), blue_light);
  const vector<string> lines = wrap_text(measure, names, width - px(32));
  for (size_t index = 0; index < lines.size(); ++index)
    add_text(player_components, app, px(16), px(4 + index * 18), lines[index],
             px(11), blue_light);
  player_components->setContentHeight(px(4 + lines.size() * 18));
}

void Environment::show_items() {
  for (Component* component : item_components->children) delete component;

  item_components->children.clear();
  int index = 0;
  for (const string& item : items) {
    const int y = px(5 + index * 34);
    add_text(item_components, app, px(16), y, "ITEM", px(10), blue_light,
             px(1));
    add_text(item_components, app, px(70), y, item, px(11), text_color);

    item_components->children.push_back(new Button(
        app, width - px(63), y - px(5), px(47), px(24), "TAKE",
        [this, item]() {
          server->request("TAKE " + item);
          actualize = true;
        },
        {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
        {11, 26, 46, 255}, 10, 1, true));
    add_row_rule(item_components, app, px(16), y + px(26), width - px(16));
    ++index;
  }
  item_components->setContentHeight(px(5 + index * 34));
}

void Environment::look() {
  const string response = server->request("LOOK");
  if (response.compare(0, 2, "OK") != 0) return;

  const json response_data = json::parse(response.substr(2));
  const json room = response_data.at("room");
  room_id->text = "LOCATION // " + room.at("id").get<string>();
  transform(room_id->text.begin(), room_id->text.end(), room_id->text.begin(),
            [](unsigned char character) {
              return static_cast<char>(toupper(character));
            });
  room_name->text = room.at("name").get<string>();
  const string description = room.at("description").get<string>();
  for (Component* component : room_description->children) delete component;
  room_description->children.clear();
  Text description_measure(app, 0, 0, "", px(12), muted);
  const vector<string> description_lines =
      wrap_text(description_measure, description, room_description->width);
  for (size_t index = 0; index < description_lines.size(); ++index)
    add_text(room_description, app, 0, px(index * 16), description_lines[index],
             px(12), muted);
  room_description->setContentHeight(px(description_lines.size() * 16));

  const json exits = room.at("exits");
  north_button->enabled = exits.contains("north");
  south_button->enabled = exits.contains("south");
  west_button->enabled = exits.contains("west");
  east_button->enabled = exits.contains("east");

  items = response_data.at("items").get<vector<string>>();
  players = response_data.at("players").get<vector<string>>();
  npcs = response_data.at("npcs").get<vector<string>>();

  show_items();
  show_players();
  show_npcs();
}
