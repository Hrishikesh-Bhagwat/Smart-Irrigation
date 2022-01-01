// SensorDataChart.js
import React from 'react';
import { Line } from 'react-chartjs-2';

const SensorDataChart = ({ sensorData }) => {
  const data = {
    labels: ["Moisture","Temperature"],
    datasets: [
      {
        label: 'Moisture',
        data: sensorData.moisture,
        fill: false,
        borderColor: 'blue',
      },
      {
        label: 'Temperature',
        data: sensorData.temperature,
        fill: false,
        borderColor: 'red',
      },
      // Add more datasets as needed
    ],
  };

  return <Line data={data} />;
};

export default SensorDataChart;