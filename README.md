# ArduinoTemperatureSensor

This project was completed as part of a group assignment for a university course, focusing on collaborative development. The primary objective was not only programming but also working together to develop a product from start to finish. Communication between group members played a crucial role in achieving our goals, involving planning sprints, task allocation, and weekly meetings. We treated the process as if we were delivering a project to stakeholders.

**Note:** _I only have access to the Arduino code, and I have permission to host it here. The complete project, including the webpage and database components, is not available in this repository. This is because I wasn't responsible for writing the webpage or the database. This is why you are only seeing a portion of the project in this repository. I may come back to this later and provide a complete example using my own code, but that would require me to purchase an Arduino kit, as the one used for the project was provided by the university._

## Project Description

The goal of the project was to design and implement a temperature sensing system using an Arduino kit. As the Embedded Developer, my responsibilities included designing and building the Arduino circuit, as well as writing the code to collect temperature readings, control an LED based on the temperature (Green = cold, yellow = fine, red = hot), and post the results to a webpage. Other roles in the group included web developers, project manager, business manager, and database administrator. The webpage would display the live data and send the data to a database. Any historical data could then be viewed and filtered. The web page also included graphs to plot the temperature of the room over time. The Arduino code would also accept temperature thresholds from the webpage that would define which temperatures are too cold or too hot.

## Features

- Reads the temperature of a room using Arduino sensor module.
- Controls an LED based on the temperature (Green = cold, yellow = fine, red = hot).
- Sends temperature data to a webpage for visualization.
- Allows users to define temperature thresholds for "too hot" and "too cold."
- Visualizes historical temperature data on the webpage.

## Project Setup

<img src="https://github.com/JoeCastle/ArduinoTemperatureSensor/assets/37884244/3250672a-29ca-4394-b22d-cbe3c2cfd40e" alt="Circuit Diagram" width="300" />
<img src="https://github.com/JoeCastle/ArduinoTemperatureSensor/assets/37884244/f33ff4f7-1324-4b26-b7b1-d25991b732f2" alt="Circuit Image" width="300" />
<img src="https://github.com/JoeCastle/ArduinoTemperatureSensor/assets/37884244/a95e5488-9a75-4257-8f5a-3ac0ad74a0c7" alt="Arduino Circuit Photo" width="300" />

## Roles and Responsibilities

- **Embedded Developer (Me):** Designed and built the Arduino circuit, wrote code for temperature readings, LED control, and data posting to the webpage.
- **Web Developers:** Developed and maintained the webpage for visualizing temperature data. Collaborated with the Embedded Developer to ensure seamless integration between the embedded system and the web interface.
- **Project Manager:** Oversaw the project's progress, coordinated team efforts, and ensured adherence to project timelines. Facilitated communication and collaboration among team members.
- **Business Manager:** Handled project budgeting, resource allocation, and any business-related aspects. Worked on project documentation and presentations.
- **Database Administrator:** Managed the storage and retrieval of temperature data on the backend. Ensured the database's integrity and collaborated with Web Developers for seamless data flow between the embedded system and the database.

## License

This project is licensed under the [MIT License](LICENSE). See the [LICENSE.md](LICENSE) file for details.
