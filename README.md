# 🌟 **SW1P1 - Project 1 by SW1** 🌟

Welcome to **Project 1**! This repository contains everything you need to set up, build, and run the project. Follow the instructions below to get started quickly, whether you're using **macOS**, **Linux**, or **Windows**.

---

## 🚀 **Getting Started**

Follow these steps to set up the project on your machine.

### 🔧 **Prerequisites**

Before you begin, ensure you have the following tools installed:

- **Homebrew** (for macOS/Linux package management)
- **CMake** (to build the project)
- **cURL** and **JSON-C** (project dependencies)

### 💻 **For Windows Users**

If you're using **Windows**, you will need **WSL (Windows Subsystem for Linux)** to work with these tools:

1. **Install WSL**:
   
   - Open **PowerShell** as Administrator and run the following command:

     ```powershell
     wsl --install
     ```

   - Follow the prompts to complete the WSL installation (it will install a Linux distribution, such as Ubuntu).

2. **Install Homebrew on WSL**:
   
   Once you have WSL set up, install **Homebrew** by running this in your **WSL terminal** (e.g., Ubuntu):

   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"


🛠️ Installing Dependencies
Step 1: Install cURL, CMake, and JSON-C
Step 2: Create a Build Directory and Generate Build Files with CMake + make the project:

```brew install curl
brew install cmake
brew install cjson´´´

```mkdir build
cd build
cmake ..
make```
