Emergency Response Game
=======================

Scenario Builder
----------------

This is the scenario builder for the Emergency Response Game,
Portland State University Capstone Senior Project - completed
Winter 2013 by Team Banana for Clark College.

**Recently Added**

* Partially loads scenario from JSON file.
* Partially displays Floor Widget for editing details for a Floor.

**Previously Added**

* Initial version just created.
* New scenarios can be created.
* Player dialog shows X, Y, Z, and facing start values as well as starting inventory items.
* Editing player dialog values persists (the scenario objects are updated).
* Inactive Props can be added (when creating new scenario).
* Floors, Conversations, Triggers can be added when creating new scenario.
* Floors, Conversations, Triggers, Inactive Props can be removed. Have stubbed edit buttons too.
* Shortcut keys for adding Floors (Ctrl+Shift+F), Conversations (Ctrl+Shift+C), Triggers (Ctrl+Shift+T),
  and Inactive Props (Ctrl+Shift+P). Also for opening Player Properties (Ctrl+P) and Annotations (Ctrl+A).
* Inactive features of application are now indicative of this nature via warning messages (and timers work).

**To do**

* Open Scenario - Parsing JSON: http://qtwiki.remdex.info/Parsing_JSON_with_QT_using_standard_QT_library
  (In Progress)
* Save Scenario to JSON.

**To do later**

* Trigger Tracker - more details on triggers (how they are started, how many entry points they have, etc)
* Objective Tracker - same as trigger tracker, for objectives
* Prop Manager - e.g. When adding inactive props, be able to search the prop collection
