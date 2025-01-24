
---

# Milky Way Galaxy Simulation

This project is a **real-time simulation of the Milky Way Galaxy**, visualized using OpenGL. It models the gravitational interactions of stars within a galaxy, incorporating the influence of a dark matter halo and dynamic star properties like brightness and temperature. The simulation is interactive and allows for user control over speed and playback.

## Features

- **Star Dynamics**: Simulates gravitational interactions between stars and a dark matter halo.
- **Dynamic Colors**: Stars are color-coded based on temperature, brightness, and mass, following astrophysical principles.
- **Real-Time Interactivity**: Adjust the simulation speed or pause it using keyboard controls.
- **Graphical Visualization**: Rendered in OpenGL with dynamic updates for smooth and visually appealing animations.
- **Randomized Galaxy Generation**: Stars are initialized in a disk-like distribution to mimic a spiral galaxy.

## How It Works

- **Stars**: Each star has properties such as position, velocity, mass, temperature, and brightness.
- **Gravitational Forces**: Calculated using a simplified model, including a contribution from a massive dark matter halo.
- **Orbits**: Stars move in approximately circular orbits, perturbed by the gravitational interactions with other stars.
- **Dynamic Updates**: The galaxy evolves in real-time, with stars changing positions and velocities.

---

## Screenshots

![Galaxy Simulation Screenshot](path/to/screenshot.png)  
*Example of the galaxy simulation with stars of varying colors and brightness.*

---

## Getting Started

### Prerequisites

- A C++ compiler with OpenGL and GLUT support.
- Libraries required:
  - OpenGL (GL)
  - GLUT (GLUT)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/milky-way-simulation.git
   cd milky-way-simulation
   ```

2. Compile the code:
   ```bash
   g++ galaxy_simulation.cpp -o galaxy_simulation -lGL -lGLU -lglut -lm
   ```

3. Run the simulation:
   ```bash
   ./galaxy_simulation
   ```

---

## Controls

- **`f`**: Speed up the simulation.
- **`s`**: Slow down the simulation.
- **`p`**: Pause/resume the simulation.

---

## Code Overview

### Main Components

- **Star Structure**: Represents individual stars with properties such as position, velocity, mass, temperature, and brightness.
- **Galaxy Initialization**: Generates a disk-like distribution of stars with randomized properties.
- **Gravitational Forces**: Simulates interactions between stars and the influence of a dark matter halo.
- **Rendering**: Uses OpenGL to visualize the galaxy, with stars displayed as points color-coded based on their temperature and brightness.
- **Interactivity**: Keyboard input is handled to control simulation speed and playback.

---

## Customization

You can adjust the following parameters in the code to modify the simulation:

- **Number of Stars (`NUM_STARS`)**: Default is `1000`.
- **Galaxy Radius (`GALAXY_RADIUS`)**: Default is `50.0f`.
- **Gravitational Constant (`GRAVITATIONAL_CONSTANT`)**: Default is `0.0001f`.
- **Dark Matter Halo Mass (`DARK_MATTER_HALO_MASS`)**: Default is `1e6`.

---

## Future Enhancements

- Add spiral arm structures for a more realistic galaxy model.
- Implement collisions and mergers between stars.
- Introduce supermassive black hole dynamics at the galactic center.
- Support for 3D visualization and rotation.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Acknowledgments

- OpenGL and GLUT documentation for providing the foundation for rendering.
- Astrophysical principles for inspiring the simulation design.

---
