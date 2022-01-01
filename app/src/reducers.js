// reducers.js
const initialState = {
    sensorData: null,
};

const rootReducer = (state = initialState, action) => {
    switch (action.type) {
        case 'UPDATE_SENSOR_DATA':
            return {
                ...state,
                sensorData: action.payload,
            };
        default:
            return state;
    }
};

export default rootReducer;
