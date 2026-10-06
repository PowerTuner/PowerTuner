# PowerTuner

Qt hybrid desktop/handheld client for [PowerTunerDaemon](https://github.com/PowerTuner/PowerTunerDaemon).

## Features

- multi-platform
- keyboard/mouse navigation
- gamepad navigation (powered by [SDL](https://github.com/libsdl-org/SDL))
- built-in [SDL game controller DB](https://github.com/mdqinc/SDL_GameControllerDB), or your own override from disk
- keyboard and gamepad custom mappings

---

### Default keyboard mapping
| Action | Key |
|---|---|
| Navbar Up | `F1` |
| Navbar Down | `F2` |
| Refresh (_read from daemon_) | `F5` |
| Apply (_send to daemon_) | `F6` |
| Move Up | `↑ Up` |
| Move Down | `↓ Down` |
| Move Left | `← Left` |
| Move Right | `→ Right` |
| Fast Left | `Home` |
| Fast Right | `End` |
| Action / Confirm | `Return` |
| Back / Cancel | `Esc` |
| Scroll Up | `Page Up` |
| Scroll Down | `Page Down` |
| Scroll to Top | `F3` |
| Scroll to Bottom | `F4` |
| Input Mode | `Tab` |

### Default gamepad mapping
| Action | Button |
|---|---|
| Navbar Up | `L1` |
| Navbar Down | `R1` |
| Refresh | `START` |
| Apply | `SELECT` |
| Move Up | `DPAD_UP` |
| Move Down | `DPAD_DOWN` |
| Move Left | `DPAD_LEFT` |
| Move Right | `DPAD_RIGHT` |
| Fast Left | `L2` |
| Fast Right | `R2` |
| Action / Confirm | `A / B / X` |
| Back / Cancel | `B / A / ○` |
| Scroll Up | `ANALOG_RIGHT_UP` |
| Scroll Down | `ANALOG_RIGHT_DOWN` |
| Scroll to Top | `ANALOG_RIGHT_LEFT` |
| Scroll to Bottom | `ANALOG_RIGHT_RIGHT` |
| Input Mode | `Y / X / △` |
| App Combo Slot 1 | `L1` |
| App Combo Slot 2 | `X / Y / □` |
| App Combo Slot 3 | `DPAD_DOWN` |

---

image generator tool was used for tray and app icons