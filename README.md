# Problem 103 - Slay the Balatro

**ACMOJ Problem ID**: 2977

## Table of Contents

- [Problem 103 - Slay the Balatro](#problem-103-slay-the-balatro)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **2977. Slay the Balatro** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/103/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

zxsheather 爱打牌。他发明了一款新的卡牌游戏，叫做 Slay the Balatro。他非常自豪于这款游戏，并希望你能帮他实现这个游戏的服务端。至于具体的游戏规则，zxsheather 已经写在了`rule.pdf`里，请仔细阅读。
## 实现要求
下发的代码文件一共有两个，分别是：
- `main.cpp`：主程序入口，负责读取输入并调用游戏控制器处理命令，你可以修改其中的任意内容已实现自定义的调试与测试功能。
- `game.h`：游戏逻辑实现文件，你需要在这个文件中实现游戏的各种功能。你需要在现有的代码基础上完成剩余的函数与类的实现。注意，请**不要修改已有**的函数声明与类的成员变量定义。

## 测试
为了帮助你调试与测试代码，好心的助教下发了所有的测试用例与一个自动化测试脚本。具体请参考`test.pdf`
## 提交
在ACMOJ上提交时，你只需要提交`game.h`文件即可。为了保证不出现编译错误，即使你没有实现某接口，也请确保该接口有一个空实现。
## 注意事项
- 为了方便提交，`game.h`的前半部分为函数声明和类定义，后半部分为实现。在完成这道题目时，你可以在前半部分添加新的函数声明，成员变量等，在文件后半部分实现这些函数。
- 由于定义和实现在同一个文件（`game.h`）中，IDE可能会报一些警告。这是正常的，你可以忽略这些警告。
- 在开始实现之前，请务必仔细阅读`rule.pdf`，理解游戏规则与各个功能的要求。

### Input Format

见下发文件

### Output Format

见下发文件

### Samples

No sample data provided for this problem.

### Data Constraints



## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 256 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/103/data_test/`.

Attachments and starter files for this problem are located at `/workspace/data/103/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
