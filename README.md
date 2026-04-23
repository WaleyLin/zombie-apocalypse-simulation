# Zombie Apocalypse Simulation

A cellular automaton zombie outbreak simulator — available as a standalone browser app **and** a compiled C++ terminal program.

---

## Files in This Repo

| File | Description |
|------|-------------|
| `zombie_apocalypse.html` | Browser version — open in any browser, no install needed |
| `zombie.cpp` | C++ version — compile and run in a terminal |
| `README.md` | This file |

---

## Quick Start (Browser — No Install Required)

1. Download `zombie_apocalypse.html`
2. Double-click the file to open it in Chrome, Firefox, Edge, or Safari
3. Adjust the sliders, hit **Start Simulation**, and watch the apocalypse unfold

That's it. No server, no Node, no dependencies.

---

## Running the C++ Version

### Requirements

| Tool | Version |
|------|---------|
| g++ / clang++ | C++11 or later |
| Any OS | Windows, macOS, Linux |

### Compile

```bash
g++ -std=c++11 -O2 -o zombie zombie.cpp -lm
```

### Run

```bash
./zombie
```

You'll be prompted for:

- **Map width** (4–40)
- **Map height** (4–40)
- **Bite accuracy** (0.0–1.0) — how likely a bite attempt succeeds
- **Berserker probability** (0.0–1.0) — chance an infected turns into a Berserker
- **Max zombie strength** (1–100) — strength at which a zombie dies and returns human

---

## How the Simulation Works

Each cell on the grid holds one entity. Every day (tick), the following happens in order:

### 1. Infected → Zombie Conversion
Any cell marked `INFECTED` that has been infected for more than 1 day turns into either a **Zombie** or a **Berserker**, based on the berserker probability.

### 2. Zombie Biting
- **Bitey Zombie** (`#` / red dot): Picks one random adjacent human and attempts a bite.
- **Berserker Zombie** (`O` / orange dot): Attempts to bite **all** adjacent humans in a single turn.

A bite succeeds with probability:

```
bite_chance = zombie_strength × bite_accuracy / 10
```

On a successful bite the human becomes `INFECTED` and gains a strength value that determines how dangerous they'll be when they turn.

### 3. Aging
Every zombie gains +1 strength per day. Once a zombie reaches **max strength**, it dies and reverts to a human. This creates natural die-off waves that can tip the simulation in humanity's favour.

---

## Entity Reference

| Symbol | Browser Color | Meaning |
|--------|--------------|---------|
| `.`    | Green dot    | Healthy human |
| `*`    | Yellow dot   | Infected (will turn next day) |
| `#`    | Red dot      | Bitey Zombie — bites one neighbor |
| `O`    | Orange dot   | Berserker — bites all neighbors |

---

## Browser vs C++ Differences

| Feature | Browser | C++ |
|---------|---------|-----|
| Visual map | Canvas (color dots) | ASCII characters |
| Real-time controls | Sliders, pause/step | Terminal prompts |
| Speed control | Slider | Instant output |
| Grid size | Up to 60×60 | Up to 40×40 |
| Step-by-step mode | Yes | No |
| Statistics panel | Live counters | Printed each day |

---

## Improvements Made (from Original)

### Bug Fixes
- Fixed off-by-one boundary checks that could access out-of-bounds memory on the east and south edges
- Fixed infected-same-day conversion — the original `a3` cooldown array had inconsistent handling; the new version uses a clean 1-day cooldown before conversion
- Berserker `length == 4` clamp removed — original code silently dropped one neighbor; now all neighbors are processed correctly

### Logic Improvements
- Initial zombie placement supports **multiple zombies** (configurable), each placed randomly without collision
- Zombie aging and reversion to human now applies correctly to **both** Zombie and Berserker types (original only partially handled Berserkers)
- Bite power calculation no longer clamps `random < 0.1` cases with a magic constant — minimum power is cleanly enforced as `Math.max(1, ...)`

### Code Quality
- All three 2D arrays (`a1`, `a2`, `a3`) replaced with typed arrays for better cache performance in the browser version
- Neighborhood scanning extracted into a reusable `getNeighbors()` function — eliminates the ~60 lines of duplicated east/south/west/north logic in the original
- Simulation loop separated from rendering and statistics — each concern has its own function

### Browser-Specific Additions
- Full visual canvas renderer with colored cells and per-zombie strength indicator bars
- Live statistics: humans, zombies, berserkers, infected, zombie-spread progress bar
- Pause / resume / single-step controls
- Event log with color-coded messages
- Speed slider (real-time, no restart needed)
- Win/lose/stalemate overlay

---

## Parameter Tuning Guide

| Goal | Suggested Settings |
|------|--------------------|
| Humans usually win | Bite accuracy 0.3–0.4, Max strength 6–8 |
| Zombies usually win | Bite accuracy 0.7–0.9, Max strength 15+ |
| Fast chaotic games | Berserker chance 0.4+, large grid |
| Slow strategic games | Bite accuracy 0.4, Max strength 10, small grid |
| Stalemate likely | Bite accuracy ~0.5, Max strength 10, medium grid |

---

## License

This project is provided as-is for educational use.
