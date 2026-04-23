# Linux Mini Shell

## Author

Om Bidikar

---

## About the Project

This project is a custom implementation of a Linux command-line shell written in C.

It supports execution of both internal and external commands, along with advanced features such as piping, job control, and signal handling, closely mimicking the behavior of a Unix shell.

---

## Features

* Execute external Linux commands
* Built-in commands: `cd`, `pwd`, `echo`, `exit`
* Command parsing and execution
* Support for piping (`|`)
* Job control (`jobs`, `fg`, `bg`)
* Signal handling (`Ctrl+C`, `Ctrl+Z`)
* Customizable shell prompt

---

## 📁 Project Structure

Linux_Mini_Shell/

Source Files:

* src/ (main.c, scan_input.c, get_command.c, execute_command.c, jobs.c)

Header Files:

* include/ (main.h)

Command List:

* external_commands.txt

Build:

* Makefile

Documentation:

* README.md

---

## ⚙️ How to Compile

```bash
make
```

---

## ▶️ How to Run

```bash
./a.out
```

---

## 🧪 Example Commands

Basic Commands:

```bash
ls
pwd
date
```

Built-in Commands:

```bash
cd ..
echo hello
exit
```

Pipes:

```bash
ls | grep .c
```

Job Control:

```bash
sleep 10 &
jobs
fg
bg
```

---

## 🧠 Concepts Used

* Process Management (`fork`, `exec`, `wait`)
* Inter-process Communication (pipes)
* Signal Handling (`SIGINT`, `SIGTSTP`)
* Command Parsing
* Job Control Mechanism
* Linux System Calls

---

## ⚠️ Limitations

* Limited support for complex command chaining
* Basic parsing logic
* No support for advanced shell features like scripting

---

## 💡 How It Works

The shell continuously reads user input, parses it into commands and arguments, and determines whether it is an internal or external command.

For external commands, a child process is created using `fork()`, and execution is handled using `execvp()`.
For piped commands, multiple processes are created and connected using pipes.

Signal handling allows process control such as stopping (`Ctrl+Z`) and interrupting (`Ctrl+C`) processes.

---

## 📘 License

This project is for learning purposes.
