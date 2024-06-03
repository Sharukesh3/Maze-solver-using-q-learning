# Maze-Solver Using Q-Learning
![mazeSolver](https://github.com/Sharukesh3/Maze-solver-using-q-learning/assets/161855868/25325a17-79af-4d0a-ba78-a3f337318aa3)

## Overview
Welcome to the Maze-Solver Robot project! This project leverages reinforcement learning, specifically Q-learning, to navigate and solve mazes. The learning algorithm runs on a laptop, which sends instructions to the robot in real-time. The robot then moves accordingly to solve the maze.

## Features
- **Q-learning Algorithm**: Utilizes reinforcement learning to teach the robot how to solve mazes efficiently.
- **Real-Time Control**: Sends instructions from the laptop to the robot to navigate the maze in real-time.
- **OpenAI Gym Environment**: Uses the gym-maze environment for training the model before deploying it on the robot.

## Hardware Requirements
- **Microcontroller**: ESP32
- **Motors**: 2 DC motors with wheels
- **Motor Driver**: L298N Motor Driver
- **Sensors**: 3 infrared sensors for obstacle detection
- **Power Supply**: Powerbank
- **Chassis**: Robot chassis kit
- **Communication Module**: Built-in Wi-Fi module on the ESP32 for communication between the laptop and the robot

## Software Requirements
- Python 3.6+
- pip (Python package installer)

## Usage
1. **Clone the Repository**:

    ```bash
    git clone https://github.com/Sharukesh3/Maze-solver-using-q-learning
    ```

2. **Install the Requirements**:

    ```bash
    pip install -r requirements.txt
    ```

3. **Clone the gym_maze Environment**:

    ```bash
    git clone https://github.com/MattChanTK/gym-maze
    cd gym-maze
    python setup.py install
    ```
    Note: The model will be downloaded during the first run.

4. **Run the Code**:

    ```bash
    python qlearning.py
    ```

## System Requirements
- **Operating System**: Windows, macOS, or Linux
- **RAM**: Minimum 4GB
- **Dependencies**: Listed in requirements.txt

## Feedback
Your feedback is valuable for improving this project. Feel free to contribute or report any issues you encounter.

## Disclaimer
This project is a prototype for educational purposes and may not work perfectly in all environments. For best results, ensure the maze setup is stable and the robot is properly calibrated.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments
Thank you for using the Maze-Solver Robot project! We hope it enhances your understanding of reinforcement learning and robotics.

## Contact
For any inquiries, please contact us at:


- [sharukesh@gmail.com](mailto:sharukesh@gmail.com)
- [shayanathif13@gmail.com](mailto:shayanathif13@gmail.com)
- [rdeva6046@gmail.com](mailto:rdeva6046@gmail.com)
- [p8001479@gmail.com](mailto:p8001479@gmail.com)

---
This README file provides a comprehensive guide for users to understand and utilize the Maze-Solver Robot project effectively.
