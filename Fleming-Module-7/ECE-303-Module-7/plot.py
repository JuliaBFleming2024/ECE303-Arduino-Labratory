import serial
import matplotlib.pyplot as plt
import numpy as np

# Open a serial connection
ser = serial.Serial('COM3', 9600)  # Replace 'COM3' with your Arduino's port

# Read and parse serial data
angles = []
distances = []
for _ in range(37):  # Assuming you have 37 readings from -90 to 90 in 5-degree increments
    line = ser.readline().decode('utf-8').strip()
    angle, distance = map(float, line.split(','))
    angles.append(angle)
    distances.append(distance)

# Convert angles to radians for polar plot
angles_rad = np.radians(angles)

# Plot the polar plot
plt.polar(angles_rad, distances)
plt.title('Two-way Angular Acceptance')
plt.show()

# Close the serial connection
ser.close()
