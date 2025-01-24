#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constants for the simulation
const int NUM_STARS = 1000; // Number of stars
const float GALAXY_RADIUS = 50.0f; // Approx radius of the galaxy
const float GRAVITATIONAL_CONSTANT = 0.0001f; // Simplified gravitational constant
const float DARK_MATTER_HALO_MASS = 1e6; // Mass of the dark matter halo
const float TIME_STEP = 0.1f; // Time increment for simulation
const float BASE_ROTATION_SPEED = 0.005f; // Base speed for differential rotation

// Simulation control variables
float rotationSpeedMultiplier = 1.0f;
bool isPaused = false;

// Star structure
struct Star {
    float x, y;  // Position in 2D space
    float vx, vy; // Velocity in 2D space
    float mass;  // Mass of the star
    float brightness; // Brightness of the star (based on age or proximity)
    float temperature; // Temperature of the star (in arbitrary units)
};

std::vector<Star> stars; // List of stars in the galaxy

// Function to calculate the gravitational force
void calculateGravitationalForces() {
    for (size_t i = 0; i < stars.size(); ++i) {
        float fx = 0.0f, fy = 0.0f;

        for (size_t j = 0; j < stars.size(); ++j) {
            if (i == j) continue; // Skip self-interaction

            float dx = stars[j].x - stars[i].x;
            float dy = stars[j].y - stars[i].y;
            float distance = sqrt(dx * dx + dy * dy + 0.01f); // Add softening factor

            float force = GRAVITATIONAL_CONSTANT * stars[i].mass * stars[j].mass / (distance * distance);
            fx += force * (dx / distance);
            fy += force * (dy / distance);
        }

        // Dark matter halo influence (simplified spherical potential)
        float r = sqrt(stars[i].x * stars[i].x + stars[i].y * stars[i].y);
        float haloForce = GRAVITATIONAL_CONSTANT * DARK_MATTER_HALO_MASS * stars[i].mass / (r * r + 0.1f);
        fx -= haloForce * (stars[i].x / r);
        fy -= haloForce * (stars[i].y / r);

        // Update velocity based on force
        stars[i].vx += fx * TIME_STEP;
        stars[i].vy += fy * TIME_STEP;
    }
}

// Initialize the galaxy with stars
void initializeGalaxy() {
    for (int i = 0; i < NUM_STARS; ++i) {
        Star star;

        // Randomize initial position in a disk
        float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;
        float radius = static_cast<float>(rand()) / RAND_MAX * GALAXY_RADIUS;
        star.x = radius * cos(angle);
        star.y = radius * sin(angle);

        // Initial velocity (circular orbit approximation)
        float v_circular = sqrt(GRAVITATIONAL_CONSTANT * DARK_MATTER_HALO_MASS / (radius + 0.1f));
        star.vx = -v_circular * sin(angle);
        star.vy = v_circular * cos(angle);

        // Assign random mass and temperature
        star.mass = 1.0f + static_cast<float>(rand()) / RAND_MAX * 0.1f;
        star.temperature = 3000.0f + static_cast<float>(rand()) / RAND_MAX * 30000.0f; // 3000K to 33000K

        // Brightness is inversely proportional to distance from the center
        star.brightness = 1.0f - radius / GALAXY_RADIUS;

        stars.push_back(star);
    }
}

// Function to determine star color based on temperature and brightness
void setStarColor(const Star& star) {
    float t = star.temperature;

    if (t > 20000.0f) {
        // Blue for very hot stars
        glColor3f(0.5f * star.brightness, 0.5f * star.brightness, star.brightness);
    }
    else if (t > 10000.0f) {
        // White for slightly cooler stars
        glColor3f(star.brightness, star.brightness, star.brightness);
    }
    else if (t > 6000.0f) {
        // Yellow for intermediate stars
        glColor3f(star.brightness, star.brightness * 0.9f, 0.5f * star.brightness);
    }
    else if (t > 4000.0f) {
        // Orange for cooler stars
        glColor3f(star.brightness * 0.9f, 0.6f * star.brightness, 0.3f * star.brightness);
    }
    else {
        // Red for the coolest stars
        glColor3f(star.brightness, 0.3f * star.brightness, 0.3f * star.brightness);
    }
}

// Update the galaxy for one timestep
void updateGalaxy() {
    calculateGravitationalForces();

    for (auto& star : stars) {
        // Update position based on velocity
        star.x += star.vx * TIME_STEP * rotationSpeedMultiplier;
        star.y += star.vy * TIME_STEP * rotationSpeedMultiplier;
    }
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (const auto& star : stars) {
        setStarColor(star);
        glVertex2f(star.x / GALAXY_RADIUS, star.y / GALAXY_RADIUS);
    }
    glEnd();

    glutSwapBuffers();
}

// Timer function for animation
void timer(int value) {
    if (!isPaused) {
        updateGalaxy();
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // Approximately 60 FPS
}

// Keyboard input for controlling the simulation
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f': // Speed up the simulation
        rotationSpeedMultiplier *= 1.5f;
        break;
    case 's': // Slow down the simulation
        rotationSpeedMultiplier /= 1.5f;
        break;
    case 'p': // Pause/resume the simulation
        isPaused = !isPaused;
        break;
    default:
        break;
    }
}

// OpenGL initialization
void initializeOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glPointSize(2.0f); // Slightly larger points for stars
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 2D orthographic projection
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Milky Way Galaxy Simulation with Dynamic Colors");

    // Initialize the galaxy
    initializeGalaxy();

    // Set up OpenGL
    initializeOpenGL();

    // Register display, timer, and keyboard functions
    glutDisplayFunc(display);
    glutTimerFunc(16, timer, 0);
    glutKeyboardFunc(handleKeyboard);

    // Start the main loop
    glutMainLoop();

    return 0;
}
