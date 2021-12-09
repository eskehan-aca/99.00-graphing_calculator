# Work Report
## Name: <ins> Elizabeth Skehan </ins>
*FALL 2021 | CS003A | GRAPHING CALCULATOR FINAL PROJECT*

## Features: 🌟
*may not be up to date*
- enter equation
  - wait for unique equation
  - modify selected equation 
- display help menu
- save file
- load file
- reset calculator
- center origin
- reset view (home)
- force update equation
- pan with arrow keys
- zoom with +/- keys
- display graph's info
- edit number of points plotted
- display equation of current graph
- display equation history
  - right click to graph selected
  - left click to delete selected from history
- display mouse coordinates
- display graph mode + status messages

### ASSIGNMENT REQUIREMENTS: 📌
*as explicitly listed from canvas/discord*
- ✅ user input from screen
- ✅ clickable equation history 
- ✅ equation history (save, load) 
- ✅ user interactions (zoom, pan)
- ✅ math functions (trig, log, abs, sqrt, unary minus)
- ✅ demonstrative video (+ readme embed)
- ❎ commented code
- ❎ testing suite --> see previous git repos

### REFLECTIONS: 💬
- project organization
  - needing to establish design guidelines (clearly outlining what should be handled by what class, hierarchies, rules, design structure, etc). 
  - keeping track of implemented features as they are created
  - removing unused constants
- time management/future
  - prioritizing more important features rather than 'fun' ones
  - having a project overview/goal setting?
  - having the project feel less manually hardcoded --> ie: have more settings/features be user editable. i think sfml and the design/visual aspect of this project did feel much 'clunkier,' outdated, or time consuming. would like to see how this project can be implemented with a display that is less hard coded? --> brancing into other areas of cs
  - developing a personal workflow w/ cs projects and assignments :)
  - figuring out code design and formatting preferences
- environment (not as important)
  - unsure how to include testing/link previous git repos/histories

### KNOWN BUGS: 🐛
*these are not hard to correct, i just haven't gotten around to it yet*
- missing points w/ transparency
- animate class -> "locked" into calc modes


### VIDEO DEMO: 🎥
![VIDEO DEMO](ESKEHAN_GraphingCalculatorDemo.mp4)
![VIDEO DEMO](https://github.com/CS3A-classroom/99_00_final_project-elizabethskehan/blob/main/ESKEHAN_GraphingCalculatorDemo.mp4) 

<br>

---
## FOR ME
#### current:
- 🧹 move sidebar update calls from process events to animate + clean
- 🎨 keybinds/help display formatting and aesthetics
- 🐛 revisit missing points w/ transparency

#### future features/ideas:
🧹 CLEANING:
- tokenize
  - check for invalid string input
  - not to require spaces
  - accepting inconsistent variable names
  - assert statements/program crashing
- textbox
  - remove drawing / sfml?
  - revisit setText
- animate
  - "locked" into modes --> mouse coords 🐛
  - clean/minimize code
  - vector for cmds/cmd names
  - mouse input, modes
- keybinds (help display)
  - modifying keybinds
  - vector of cmds?
  - multiple pages?
  - make this into a struct
  - edit keybinds via click
- saving/loading functions
  - duplicates in immediate list
  - saved functs vs equation history
  - custom saves, save names
  - select with num keys
  - using vector??
- sidebar
  - clean drawing functions
  - update functions (update all?)
  - display graph range?
- other
  - remove excess/unused constants
  - remove function.cpp missing return types 
  - remove duplicate rpn code for var/no var
  - toggle class instantiated couts

🧮 MISC:
  - holding multiple graphinfos?
  - revisit addtl functions(pi, max, min, e?, ln, etc)
  - revisit variables
  - polar grid/polar coordinates
  - parametric equations
  - plotting coordinate points
  - picture in picture
  - plotting multiple equations
  - textbox class to modify keybinds via click help menu
  - revisit zoom scale
  - saving user settings
  - math exceptions (folder)

⌨ USER:
  - cmd input
  - keybind c/r to clear textbox
  - hover/click to display point cooordinates
  - scrolling to view more equation history
  - scrolling to zoom in / out
  - zoom dependent on cursor location?
  - panning with mouse control
  - change window size/other constants

🎨 AESTHETICS/COSMETICS:
  - closing sidebar?
  - reformat graph display
  - reformat help menu display
  - displaying grid lines (toggle)
  - change colors! (plotted points, grid lines, background)
  - rainbow points!
  - saving "color themes"