// Copyright 2026 mrazakam

#include "gui/components/features/Environment.hpp"

#include <algorithm>
#include <cmath>
#include <regex>
#include <string>
#include <vector>

#include "gui/Server.hpp"
#include "gui/json.hpp"
#include "gui/components/basic/Button.hpp"
#include "gui/components/basic/Group.hpp"
#include "gui/components/basic/Input.hpp"
#include "gui/components/basic/Line.hpp"
#include "gui/components/basic/Rect.hpp"
#include "gui/components/basic/ScrollableGroup.hpp"
#include "gui/components/basic/Text.hpp"
#include "gui/components/features/TAPInterfaceHelpers.hpp"

using std::find_if;
using std::function;
using std::lround;
using std::regex;
using std::regex_match;
using std::string;
using std::vector;
using json = nlohmann::json;
using TAPUI::add_button;
using TAPUI::add_row_rule;
using TAPUI::add_text;
using TAPUI::blue;
using TAPUI::blue_light;
using TAPUI::border;
using TAPUI::create_panel;
using TAPUI::error;
using TAPUI::muted;
using TAPUI::panel_color;
using TAPUI::panel_dark;
using TAPUI::text_color;
using TAPUI::warning;

Environment::Environment(App* app, int x, int width, int panel_height,
                         float scale, Server* server,
                         function<void(string)> log_protocol,
                         function<void()> update_hp)
    : Component(app, x, 0),
      actualize(false),
      panel(nullptr),
      server(server),
      log_protocol(log_protocol),
      width(width),
      group_popup(nullptr),
      group_popup_open(false),
      create_group_focused(false),
      join_group_focused(false),
      invite_player_focused(false),
      group_feedback(nullptr),
      quest_popup(nullptr),
      quest_components(nullptr),
      quest_feedback(nullptr),
      quest_popup_open(false),
      quest_loading(false),
      quest_refresh_pending(false),
      update_hp(update_hp) {
  px = [scale](float value) { return static_cast<int>(lround(value * scale)); };
  Group* room = create_panel(app, width, panel_height, "01 / ENVIRONMENT");
  const int room_end = width - px(16);

  room_name = add_text(room, app, px(16), px(52), "The Forgotten Archive",
                       px(17), text_color);
  room_id = add_text(room, app, px(16), px(78), "LOCATION // ARC-003", px(10),
                     blue_light, px(1));
  room_description =
      new ScrollableGroup(app, px(16), px(105), width - px(32), px(82), {});
  room->children.push_back(room_description);
  add_text(room, app, px(16), px(197), "EXITS", px(10), blue_light, px(1));
  north_button = new Button(
      app, px(82), px(190), px(62), 26, "NORTH",
      [this]() {
        this->server->request("MOVE north");
        this->look();
      },
      {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
      {65, 72, 82, 255}, 10, 1, true);
  room->children.push_back(north_button);

  south_button = new Button(
      app, px(150), px(190), px(62), 26, "SOUTH",
      [this]() {
        this->server->request("MOVE south");
        this->look();
      },
      {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
      {65, 72, 82, 255}, 10, 1, true);
  room->children.push_back(south_button);

  west_button = new Button(
      app, px(218), px(190), px(62), 26, "WEST",
      [this]() {
        this->server->request("MOVE west");
        this->look();
      },
      {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
      {65, 72, 82, 255}, 10, 1, true);
  room->children.push_back(west_button);

  east_button = new Button(
      app, px(286), px(190), px(62), 26, "EAST",
      [this]() {
        this->server->request("MOVE east");
        this->look();
      },
      {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
      {65, 72, 82, 255}, 10, 1, true);
  room->children.push_back(east_button);

  add_text(room, app, px(16), px(236), "ITEMS IN THIS ROOM", px(10), blue_light,
           px(2));
  room->children.push_back(
      new Line(app, px(16), px(258), room_end, px(258), border));

  item_components = new ScrollableGroup(app, 0, px(264), width, px(112), {});
  room->children.push_back(item_components);
  show_items();

  add_text(room, app, px(16), px(382), "NPCS", px(10), blue_light, px(2));

  room->children.push_back(
      new Line(app, px(16), px(404), room_end, px(404), border));

  npc_components = new ScrollableGroup(app, 0, px(410), width, px(85), {});
  room->children.push_back(npc_components);
  show_npcs();

  add_text(room, app, px(16), px(503), "PLAYERS PRESENT", px(10), blue_light,
           px(2));
  player_components = new ScrollableGroup(app, 0, px(523), width, px(39), {});
  room->children.push_back(player_components);
  show_players();
  room->children.push_back(
      new Line(app, px(16), px(562), room_end, px(562), border));

  int action_y = px(574);

  room->children.push_back(new Button(
      app, px(16), action_y, px(68), px(24), "QUESTS",
      [this]() {
        this->quest_popup_open = true;
        this->load_quests();
      },
      {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
      {11, 26, 46, 255}, 10, 1, true));

  room->children.push_back(new Button(
      app, px(90), action_y, px(100), px(24), "GROUP",
      [this]() { this->group_popup_open = !this->group_popup_open; },
      {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
      {11, 26, 46, 255}, 10, 1, true));

  const int popup_width = width - px(32);
  const int input_x = px(16);
  const int submit_width = px(72);
  const int field_gap = px(8);
  const int field_width = popup_width - input_x * 2 - submit_width - field_gap;
  group_popup = new Group(app, px(16), px(112), {});
  group_popup->children.push_back(
      new Rect(app, 0, 0, popup_width, px(390), panel_dark, border, px(1)));
  add_text(group_popup, app, input_x, px(14), "GROUP MANAGEMENT", px(11),
           blue_light, px(1));
  group_popup->children.push_back(new Button(
      app, popup_width - px(40), px(8), px(28), px(24), "X",
      [this]() { this->group_popup_open = false; }, panel_dark, muted, 0,
      border, {16, 39, 68, 255}, panel_dark, px(10), 0, true));
  group_popup->children.push_back(
      new Line(app, input_x, px(40), popup_width - input_x, px(40), border));

  const int section_label_size = px(10);
  const int field_height = px(32);
  auto add_group_field = [&](const string& label, int y, string& value,
                             bool& focused, const string& placeholder,
                             const string& action) {
    string* input_value = &value;
    add_text(group_popup, app, input_x, y, label, section_label_size,
             text_color);
    Input* input = new Input(
        app, input_x, y + px(18), field_width, field_height, &value, &focused,
        panel_dark, text_color, 0, border, placeholder, ">_", 31, px(11), muted,
        [this, input_value, action]() {
          this->submit_group_action(*input_value, action);
        },
        blue, blue_light);
    group_popup->children.push_back(input);
    group_popup->children.push_back(new Button(
        app, input_x + field_width + field_gap, y + px(18), submit_width,
        field_height, "SUBMIT",
        [this, input_value, action]() {
          this->submit_group_action(*input_value, action);
        },
        {11, 26, 46, 255}, blue_light, 0, border, {16, 39, 68, 255},
        {11, 26, 46, 255}, px(9), 0, true));
  };

  add_group_field("CREATE A GROUP", px(52), create_group_name,
                  create_group_focused, "Group name", "CREATE");
  add_group_field("JOIN A GROUP", px(122), join_group_name, join_group_focused,
                  "Group name", "JOIN");
  add_group_field("INVITE A PERSON", px(192), invite_player_name,
                  invite_player_focused, "Player name", "INVITE");
  add_text(group_popup, app, input_x, px(262), "LEAVE THE GROUP",
           section_label_size, text_color);
  group_popup->children.push_back(new Button(
      app, input_x, px(280), popup_width - input_x * 2, field_height,
      "LEAVE GROUP",
      [this]() { this->submit_group_action(this->member_group, "LEAVE"); },
      {11, 26, 46, 255}, {255, 151, 151, 255}, 0, {104, 49, 57, 255},
      {57, 27, 34, 255}, {11, 26, 46, 255}, px(10), 0, true));
  group_feedback =
      add_text(group_popup, app, input_x, px(330), "", px(10), muted);

  quest_popup = new Group(app, px(16), px(92), {});
  quest_popup->children.push_back(
      new Rect(app, 0, 0, popup_width, px(460), panel_dark, border, px(1)));
  add_text(quest_popup, app, input_x, px(14), "QUEST LOG", px(11), blue_light,
           px(1));
  quest_popup->children.push_back(new Button(
      app, popup_width - px(40), px(8), px(28), px(24), "X",
      [this]() { this->quest_popup_open = false; }, panel_dark, muted, 0,
      border, {16, 39, 68, 255}, panel_dark, px(10), 0, true));
  quest_popup->children.push_back(
      new Line(app, input_x, px(40), popup_width - input_x, px(40), border));
  quest_components = new ScrollableGroup(
      app, input_x, px(52), popup_width - input_x * 2, px(330), {});
  quest_popup->children.push_back(quest_components);
  quest_feedback =
      add_text(quest_popup, app, input_x, px(398), "", px(10), muted);

  panel = room;
}

void Environment::render(int origin_x, int origin_y) {
  if (quest_refresh_pending) {
    quest_refresh_pending = false;
    load_quests();
  }

  if (!group_popup_open && !quest_popup_open) {
    panel->render(origin_x + x, origin_y + y);
    return;
  }

  vector<SDL_Event> events;
  events.swap(app->events);
  panel->render(origin_x + x, origin_y + y);
  events.swap(app->events);
  if (group_popup_open) group_popup->render(origin_x + x, origin_y + y);
  if (quest_popup_open) quest_popup->render(origin_x + x, origin_y + y);
}

void Environment::submit_group_action(string& value, const string& action) {
  size_t first = value.find_first_not_of(" \t\r\n");
  size_t last = value.find_last_not_of(" \t\r\n");
  string name =
      first == string::npos ? "" : value.substr(first, last - first + 1);
  if (action != "LEAVE" && name.empty()) {
    group_feedback->text = "Enter a name before submitting.";
    group_feedback->color = error;
    return;
  }
  if (action == "LEAVE" && name.empty()) {
    group_feedback->text = "You are not currently in a group.";
    group_feedback->color = error;
    return;
  }
  if (action != "LEAVE" && name.size() > 31) {
    group_feedback->text = "Names must be 31 characters or fewer.";
    group_feedback->color = error;
    return;
  }
  if ((action == "CREATE" || action == "JOIN") &&
      name.find_first_of(" \t\r\n") != string::npos) {
    group_feedback->text = "Group names cannot contain spaces.";
    group_feedback->color = error;
    return;
  }
  if (action == "INVITE" &&
      !regex_match(name, regex("^[A-Za-z0-9_-]{2,24}$"))) {
    group_feedback->text =
        "Use 2-24 letters, numbers, _ or - for player names.";
    group_feedback->color = error;
    return;
  }

  string command = "GROUP " + action;
  if (!name.empty()) command += " " + name;
  string response = server->request(command);
  log_protocol(response);
  bool succeeded = response.compare(0, 2, "OK") == 0;
  group_feedback->text =
      succeeded ? "Success. Details are in the protocol log."
                : "Request failed. Details are in the protocol log.";
  group_feedback->color = succeeded ? blue_light : error;
  if (succeeded) {
    if (action == "CREATE" || action == "JOIN")
      member_group = name;
    else if (action == "LEAVE")
      member_group.clear();
    if (action != "LEAVE") value.clear();
  }
}

void Environment::load_quests() {
  quest_loading = true;
  quest_feedback->text = "Loading quests...";
  quest_feedback->color = muted;
  const string response = server->request("QUESTS");
  log_protocol(response);
  quest_loading = false;

  if (response.compare(0, 2, "OK") != 0) {
    quest_feedback->text = response.empty()
                               ? "Unable to load quests."
                               : "Quest request failed. See protocol log.";
    quest_feedback->color = error;
    return;
  }

  try {
    const json response_data = json::parse(response.substr(2));
    if (!response_data.is_array()) {
      quest_feedback->text = "Invalid quest data returned by server.";
      quest_feedback->color = error;
      return;
    }

    quests.clear();
    for (const json& quest_data : response_data) {
      if (!quest_data.is_object()) continue;
      Quest quest;
      quest.id = quest_data.value("quest_id", "");
      quest.status = quest_data.value("status", "unknown");
      quest.progress = quest_data.value("progress", "");
      quests.push_back(quest);
    }
    quest_feedback->text = "";
    show_quests();
  } catch (const json::exception&) {
    quest_feedback->text = "Invalid quest data returned by server.";
    quest_feedback->color = error;
  }
}

void Environment::show_quests() {
  for (Component* component : quest_components->children) delete component;
  quest_components->children.clear();

  if (quests.empty()) {
    add_text(quest_components, app, 0, 0, "No quests available.", px(11),
             muted);
    quest_components->setContentHeight(px(32));
    return;
  }

  const int row_height = px(62);
  const int button_width = px(132);
  int index = 0;
  for (const Quest& quest : quests) {
    const int row_y = index * row_height;
    const string quest_id = quest.id.empty() ? "Unknown quest" : quest.id;
    add_text(quest_components, app, 0, row_y, quest_id, px(11), text_color);
    string details = "STATUS // " + quest.status;
    if (!quest.progress.empty()) details += "    PROGRESS // " + quest.progress;
    add_text(quest_components, app, 0, row_y + px(20), details, px(9), muted);

    Button* complete_button = new Button(
        app, quest_components->width - button_width, row_y + px(5),
        button_width, px(28), "COMPLETE QUEST",
        [this, quest_id]() { this->complete_quest(quest_id); },
        {11, 26, 46, 255}, blue_light, 0, {37, 70, 107, 255}, {16, 39, 68, 255},
        {65, 72, 82, 255}, px(8), 0, true);
    complete_button->enabled = quest.status == "active" && !quest.id.empty();
    quest_components->children.push_back(complete_button);
    add_row_rule(quest_components, app, 0, row_y + px(48),
                 quest_components->width);
    ++index;
  }
  quest_components->setContentHeight(index * row_height);
}

void Environment::complete_quest(const string& quest_id) {
  if (quest_id.empty()) return;
  auto quest =
      find_if(quests.begin(), quests.end(),
              [&quest_id](const Quest& entry) { return entry.id == quest_id; });
  if (quest == quests.end() || quest->status != "active") return;

  const string response = server->request("COMPLETE_QUEST " + quest_id);
  log_protocol(response);
  if (response.compare(0, 2, "OK") == 0) {
    quest_refresh_pending = true;
  } else {
    quest_feedback->text = "Could not complete quest. See protocol log.";
    quest_feedback->color = error;
  }
}

Environment::~Environment() {
  delete panel;
  delete group_popup;
  delete quest_popup;
}
