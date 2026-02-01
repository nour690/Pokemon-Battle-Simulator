# Pokemon Battle Simulator

🎮 A **turn-based Pokémon battle simulator** written in **C**, inspired by  
https://play.pokemonshowdown.com

This project simulates core Pokémon battle mechanics such as **types, moves, damage calculation, switching, speed priority, and fainting**, all through a terminal-based interface.

> ⚠️ This is an educational **simulation**, not an official Pokémon product.

---

## 🎯 Overview

The Pokémon Battle Simulator allows two players to:

- Battle using teams of **6 randomly selected Pokémon**
- Choose between **attacking or switching Pokémon** each round
- Use real Pokémon **types, moves, stats, and effectiveness**
- Experience **speed-based turn order**
- Automatically switch Pokémon when one faints
- Play until one player has no Pokémon left

The project focuses on **core battle logic**, not graphics or networking.

---

## 🛠️ Technologies Used

- **Language:** C
- **Paradigm:** Procedural Programming
- **Concepts & Techniques:**
  - Structs and enums
  - File I/O (`.txt` data files)
  - Pointers and memory handling
  - Multi-file project organization
  - Input validation
  - Game loop logic
  - Modular design (`init.c`, `battle.c`, `main.c`)

---

## ⚔️ Battle Mechanics Implemented

Type effectiveness (including dual types)

STAB (Same-Type Attack Bonus)

Physical vs Special damage calculation

Speed-based attack order

Pokémon switching rules

Automatic faint handling

End-of-round and start-of-round state handling

---

## 💡 What I Learned

This project was a major milestone in my programming journey. Through it, I learned:

How to design and structure a large C program across multiple files

How to model real-world systems using structs

How to safely work with pointers and arrays

How to implement a game loop and state transitions

How to debug complex logic and edge cases

Why code organization and readability matter as projects grow

That low-level languages like C build strong fundamentals

---

## 🚀 How to Compile and Run
gcc -Wall -Wextra -Werror main.c init.c battle.c -o main
./main

Make sure all .txt data files are in the same directory as the executable.

---

## 📌 Notes

This project is for educational purposes only

Pokémon names, types, and moves belong to The Pokémon Company

Inspired by Pokémon Showdown, but fully implemented from scratch in C

---

## ⭐ Final Thoughts

This project helped solidify my understanding of C programming, game logic, and software structure.
It represents a big step forward in writing larger, more organized programs.

Feel free to explore, fork, or suggest improvements!

---
