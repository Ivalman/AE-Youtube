#include <iostream>

int main() {
    // you can change and play with the parameters below to see how they affect the simulation results.
    // start with changing the input_current and tau and see how they affect the firing rate of the neuron.
    // 1. Simulation parameters
    constexpr double dt = 0.1;              // time step (ms)
    constexpr double duration = 100.0;      // total simulation duration (ms)
    constexpr int num_steps = static_cast<int>(duration / dt); // number of simulation steps
    
    // 2. Neuron biological parameters (normalized scale)
    constexpr double tau = 10.0;            // membrane time constant (ms)
    constexpr double resistance = 1.0;      // membrane resistance (MOhm)
    constexpr double threshold = 1.0;       // spike threshold (mV)
    constexpr double reset = 0.0;           // resting / reset potential (mV)
    constexpr double input_current = 1.3;   // constant external current (nA)

    double voltage = reset;
    int spike_count = 0;

    // 3. Main simulation loop
    for (int step = 0; step < num_steps; ++step) {
        double current_time = (step + 1) * dt;

        // Leak and Integrate
        // Equation: tau * dV/dt = -(V - reset) + R * I
        double leak = -(voltage - reset);
        double integrate = resistance * input_current;
        voltage += (dt / tau) * (leak + integrate);

        // Fire and Reset
        if (voltage >= threshold) {
            std::cout << "Spike at " << current_time << " ms\n";
            voltage = reset;
            ++spike_count;
        }
    }

    // Summary statistics
    double firing_rate = spike_count / (duration / 1000.0); // in Hz (spikes per second)
    std::cout << "\nTotal Spikes: " << spike_count 
              << " | Firing Rate: " << firing_rate << " Hz\n";

    return 0;
}