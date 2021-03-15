# Ethernet-Switch-simulator

A basic example of understanding the logic that goes in an ethernet switch.
The in.txt contains information regarding packet deliveries. Every line is structured by frame - port - source - destination.
Source.cpp reads from this file and determines where packets should be deliver.
