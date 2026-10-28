// Copyright 2026 mrazakam

#include "gui/components/page/TAPInterface.hpp"

#include <algorithm>
#include <cmath>
#include <string>

#include "gui/Server.hpp"
#include "gui/components/basic/Group.hpp"
#include "gui/components/basic/Line.hpp"
#include "gui/components/basic/Rect.hpp"
#include "gui/components/features/Environment.hpp"
#include "gui/components/features/Header.hpp"
#include "gui/components/features/Inventory.hpp"
#include "gui/components/features/Protocol.hpp"
#include "gui/components/features/TAPInterfaceHelpers.hpp"

using std::lround;
using TAPUI::add_text;
using TAPUI::background;
using TAPUI::border;
using TAPUI::muted;

TAPInterface::TAPInterface(App* app, int width, int height, Server* server)
    : Component(app, 0, 0),
      width(width),
      height(height),
      server(server),
      screen(nullptr),
      chat_message(""),
      protocol_command(""),
      chat_focused(false),
      command_focused(false),
      header(nullptr) {
  const float scale =
      std::max(0.5f, std::min(1.0f, std::min((width - 28.0f) / 1772.0f,
                                             (height - 35.0f) / 865.0f)));
  auto px = [scale](float value) {
    return static_cast<int>(lround(value * scale));
  };
  const int canvas_width = px(1772);
  const int canvas_height = px(865);
  const int canvas_x = (width - canvas_width) / 2;
  const int panel_height = px(762);
  const int available_columns = px(1744) - px(24);
  const int left_width = available_columns * 115 / 315;
  const int middle_width = available_columns * 100 / 315;
  const int right_width = available_columns - left_width - middle_width;
  const int left_x = px(14);
  const int middle_x = left_x + left_width + px(12);
  const int right_x = middle_x + middle_width + px(12);

  Group* canvas = new Group(app, canvas_x, 0, {});
  canvas->children.push_back(
      new Rect(app, 0, 0, canvas_width, canvas_height, background));

  header = new Header(app, canvas_width, scale, server);
  canvas->children.push_back(header);
  inventory = new Inventory(app, middle_x, middle_width, panel_height, scale,
                            chat_message, chat_focused, server);
  canvas->children.push_back(inventory);
  server->tap_interface = this;

  protocol = new Protocol(app, right_x, right_width, panel_height, scale,
                          protocol_command, command_focused, server);
  canvas->children.push_back(protocol);
  environment = new Environment(
      app, left_x, left_width, panel_height, scale, server,
      [this](std::string msg) { this->protocol->log_protocol(msg); },
      [this]() { this->header->update_hp(); });
  canvas->children.push_back(environment);

  Group* footer = new Group(app, 0, px(830), {});
  footer->children.push_back(new Line(app, 0, 0, canvas_width, 0, border));
  add_text(footer, app, px(22), px(12), "TAP // SYSTEM INTERFACE", px(9), muted,
           px(2));
  canvas->children.push_back(footer);
  screen = new Group(app, 0, 0,
                     {new Rect(app, 0, 0, width, height, background), canvas});
}

void TAPInterface::update_data() {
  inventory->update_inventory();
  environment->look();
}

void TAPInterface::render(int origin_x, int origin_y) {
  if (environment->actualize || inventory->actualize) {
    environment->look();
    inventory->update_inventory();
  }
  environment->actualize = false;
  inventory->actualize = false;
  screen->render(origin_x, origin_y);
}

TAPInterface::~TAPInterface() {
  server->tap_interface = nullptr;
  delete screen;
}
