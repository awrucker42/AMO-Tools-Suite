const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'calculator' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('electricityReduction', function (t) {
    t.plan(4);
    t.type(bindings.electricityReduction, 'function');

    var inp = {
        electricityReductionInputVec: [
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 0,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            }
        ]
    };
    var res = bindings.electricityReduction(inp);
    t.equal(rnd(res.energyUse), rnd(407045.796185), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(48845.495542), 'res.energyCost is ' + res.energyCost);
    t.equal(rnd(res.power), rnd(47.111782), 'res.power is ' + res.power);

});

test('electricityReduction all calc types', function (t) {
    t.plan(3);
    t.type(bindings.electricityReduction, 'function');

    var inp = {
        electricityReductionInputVec: [
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 0,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 0,
                multimeterData: {
                    numberOfPhases: 1,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 1,
                multimeterData: {
                    numberOfPhases: 1,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 2,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 2
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 3,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 2
            }
        ]
    };
    var res = bindings.electricityReduction(inp);
    t.equal(rnd(res.energyUse), rnd(1945004.716987), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(233400.566038), 'res.energyCost is ' + res.energyCost);
});


test('Natural Gas Reduction test 1', function (t) {
    t.plan(3);
    t.type(bindings.electricityReduction, 'function');

    var inp = {
        naturalGasReductionInputVec: [
            {
                operatingHours: 8640,
                fuelCost: 0.12,
                measurementMethod: 0,
                flowMeterMethodData: {
                    flowRate: 5
                },
                otherMethodData: {
                    consumption: 30.00
                },
                airMassFlowData: {
                    isNameplate: false,
                    airMassFlowMeasuredData: {
                        areaOfDuct: 3,
                        airVelocity: 15
                    },
                    airMassFlowNameplateData: {
                        airFlow: 30
                    },
                    inletTemperature: 70,
                    outletTemperature: 800,
                    systemEfficiency: 80
                },
                waterMassFlowData: {
                    waterFlow: 10,
                    inletTemperature: 70,
                    outletTemperature: 100,
                    systemEfficiency: 80
                },
                units: 2
            }
        ]
    };

    var res = bindings.naturalGasReduction(inp);
    t.equal(rnd(res.energyUse), rnd(88992.00), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(10679.04), 'res.energyCost is ' + res.energyCost);
});


test('Compressed Air Reduction Basic Test', function (t) {
    t.plan(6);
    t.type(bindings.compressedAirReduction, 'function');

    var inp = {
        compressedAirReductionInputVec: [
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };

    var res = bindings.compressedAirReduction(inp);
    t.equal(rnd(res.energyUse), rnd(2211840.0));
    t.equal(rnd(res.energyCost), rnd(265420.8));
    t.equal(rnd(res.flowRate), rnd(200000.0));
    t.equal(rnd(res.singleNozzleFlowRate), rnd(0.0));
    t.equal(rnd(res.consumption), rnd(103680000000.0));
});

test('Compressed Air Reduction Test All', function (t) {
    t.plan(6);
    t.type(bindings.compressedAirReduction, 'function');

    var inp = {
        compressedAirReductionInputVec: [
            // flow measurement with electricity
            // energyUse = 221184000.0
            // energyCost = 26542080.0
            // flowRate = 0.0
            // singleNozzleFlowRate = 0.0
            // consumption = 103680000000.0
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // bag method with electricity
            // energyUse = 3769.9111
            // energyCost = 452.3893
            // flowRate = 3.408846
            // singleNozzleFlowRate = 0.0
            // consumption = 3534291.73528
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 1,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // pressure method, no electricity
            // flowRate = 1.778508
            // singleNozzleFlowRate = 1.778508
            // consumption = 921978.5471999
            {
                hoursPerYear: 8640,
                utilityType: 0,
                utilityCost: 0.12,
                measurementMethod: 2,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // other method with electricity
            // consumption = 200000.0
            // energyUse = 213.3333
            // energyCost = 25.6
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 3,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1                
            }
        ]
    };

    var res = bindings.compressedAirReduction(inp);
    t.equal(rnd(res.energyUse), rnd(2211881.965779));
    t.equal(rnd(res.energyCost), rnd(376063.261557));
    t.equal(rnd(res.flowRate), rnd(200005.187354));
    t.equal(rnd(res.singleNozzleFlowRate), rnd(1.778508));
    t.equal(rnd(res.consumption), rnd(103682889124.41486));
});