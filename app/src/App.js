// App.js
import React, { useEffect } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { subscribeToTopic } from './awsIoTService';
import SensorDataChart from './SensorDataChart';

const App = () => {
  const dispatch = useDispatch();
  const sensorData = useSelector((state) => state.sensorData);

  useEffect(() => {
    dispatch(subscribeToTopic());
  }, [dispatch]);

  return (
    <div>
      <h1>AWS IoT Sensor Data</h1>
      {sensorData && <SensorDataChart sensorData={sensorData} />}
    </div>
  );
};

export default App;