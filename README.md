# 🧟 Zombie Apocalypse Simulation in C++

This is a terminal-based C++ simulation that models the spread of a zombie outbreak on a grid-based map. The simulation includes both normal zombies and more aggressive berserker zombies, along with configurable parameters like infection rate, mutation chance, and maximum zombie strength before they revert to being human.

---

## 🕹️ How It Works

- The map is a grid filled with humans ('.').
- One zombie (`#`) is randomly spawned on Day 0.
- Zombies can bite adjacent humans and potentially infect them.
- Infected individuals (`*`) become either:
  - Bitey Zombies (`#`)
  - Berserker Zombies (`O`) based on mutation probability
- Berserkers infect multiple humans at once.
- Zombies grow stronger each day. If their strength exceeds a set max value, they revert back to humans.
- The simulation ends when:
  - All humans are infected/zombified (zombies win)
  - All zombies revert or fail to infect (humans win)
  - 10,000 days pass (draw)

---

## 🔢 Symbols

- `.` = Human  
- `*` = Infected  
- `#` = Bitey Zombie  
- `O` = Berserker Zombie  

---

## 🛠️ How to Run

1. **Compile** the program:
g++ -std=c++11 -o zombie_sim zombie_apocalypse_sim.cpp

markdown
Copy
Edit

2. **Run** the simulation:
./zombie_sim

yaml
Copy
Edit

3. **Follow the prompts** to enter:
- Map width and height (4–40)
- Probability of zombie bite success (0–1)
- Probability of berserker mutation (0–1)
- Maximum zombie strength before reversion (e.g., 10)

---

## 🎮 Example Simulation Output

Enter map width between 4 and 40: 10
Enter map height between 4 and 40: 10
Enter zombie bite accuracy (a float between 0-1): 0.8
Enter berserker probability (a float between 0-1): 0.2
Enter max strength zombies can be until they turn back to humans (1-100): 10
Zombie of strength 5 spawned at coordinate (3, 7)
The apocalypse has started!

. = Human

= Infected

= Bitey Zombie
O = Berserker Zombie

Day: 0
Number of Zombies: 1
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . # . .
. . . . . . . . . .

yaml
Copy
Edit

---

## 📦 Features

- Adjustable map size
- Randomized zombie behavior
- Configurable infection mechanics
- Terminal output of map state each day
- Dynamic tracking of zombie strength and behavior

---

## 🧪 Experiment Ideas

- Set bite accuracy to 1.0 and berserker chance to 0 to observe a pure infection spread.
- Try setting the max zombie strength to 3 for a faster revert rate.
- Simulate large maps (e.g., 40×40) and increase the max strength for long-term battles.

---

## 👤 Author

Waley Lin  
If you enjoyed this simulation or have ideas to improve it, feel free to contribute or reach out!

---

## 🧠 Notes

This is a fun and educational simulation designed to explore probabilistic spread, mutation dynamics, and decay mechanics in a grid-based environment using core C++ concepts.
