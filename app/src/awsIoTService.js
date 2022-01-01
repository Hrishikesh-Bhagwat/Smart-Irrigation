import AWS from 'aws-sdk';

const iotData = new AWS.IotData({
  endpoint: process.env.endpoint,
});

export const subscribeToTopic = () => (dispatch) => {
  iotData.subscribe(
    { topic: 'sensors/esp32' },
    (err, data) => {
      if (err) {
        console.error('Subscription error:', err);
      }
    }
  );

  iotData.on('message', (topic, payload) => {
    const data = JSON.parse(payload.toString());
    dispatch(updateSensorData(data));
  });
};