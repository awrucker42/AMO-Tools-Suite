#ifndef AMO_LIBRARY_ELECTRICITYREDUCTION_H
#define AMO_LIBRARY_ELECTRICITYREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>


class MultimeterData {
public:

    MultimeterData(const int numberOfPhases, const double supplyVoltage,
                   const double averageCurrent, const double powerFactor)
                 : numberOfPhases(numberOfPhases), supplyVoltage(supplyVoltage),
                   averageCurrent(averageCurrent), powerFactor(powerFactor)
                   {}

    int getNumberOfPhases() const { return numberOfPhases; }
    double getSupplyVoltage() const { return supplyVoltage; }
    double getAverageCurrent() const { return averageCurrent; }
    double getPowerFactor() const { return powerFactor; }

    void setNumberOfPhases(int numberOfPhases);
    void setSupplyVoltage(double supplyVoltage);
    void setAverageCurrent(double averageCurrent);
    void setPowerFactor(double powerFactor);

private:
    int numberOfPhases;
    double supplyVoltage, averageCurrent, powerFactor;
};

class NameplateData {
public:

    NameplateData(const double ratedMotorPower, const bool variableSpeedMotor, 
                  const double operationalFrequency, const double lineFrequency,
                  const double motorAndDriveEfficiency, const double loadFactor)
                : ratedMotorPower(ratedMotorPower), variableSpeedMotor(variableSpeedMotor),
                  operationalFrequency(operationalFrequency), lineFrequency(lineFrequency),
                  motorAndDriveEfficiency(motorAndDriveEfficiency), loadFactor(loadFactor)
                  {}

    double getRatedMotorPower() const { return ratedMotorPower; }
    bool getVariableSpeedMotor() const { return variableSpeedMotor; }
    double getOperationalFrequency() const { return operationalFrequency; }
    double getLineFrequency() const { return lineFrequency; }
    double getMotorAndDriveEfficiency() const { return motorAndDriveEfficiency; }
    double getLoadFactor() const { return loadFactor; }

    void setRatedMotorPower(double ratedMotorPower);
    void setVariableSpeedMotor(bool variableSpeedMotor);
    void setOperationalFrequency(double operationalFrequency);
    void setLineFrequency(double lineFrequency);
    void setMotorAndDriveEfficiency(double motorAndDriveEfficiency);
    void setLoadFactor(double loadFactor);

private:
    double lineFrequency;
    bool variableSpeedMotor;
    double ratedMotorPower, operationalFrequency, motorAndDriveEfficiency, loadFactor;
};

class PowerMeterData {
public:
    PowerMeterData(const double power)
                 : power(power) 
                {}

    double getPower() const { return power; }
    void setPower(double power);

private:
    double power;
};

class OtherMethodData {
public:
    OtherMethodData(const double energy)
                  : energy(energy)
                  {}

    double getEnergy() const { return energy; }
    void setEnergy(double energy);

private:
    double energy;
};


class ElectricityReductionInput {
public:

    ElectricityReductionInput(const int hoursPerDay, const int daysPerMonth, const int monthsPerYear,
                         const double electricityCost, const int measurementMethod, const MultimeterData multimeterData,
                         const NameplateData nameplateData, const PowerMeterData powerMeterData, const OtherMethodData otherMethodData,
                         const int units)
                       : hoursPerDay(hoursPerDay), daysPerMonth(daysPerMonth), monthsPerYear(monthsPerYear),
                         electricityCost(electricityCost), measurementMethod(measurementMethod), multimeterData(multimeterData),
                         nameplateData(nameplateData), powerMeterData(powerMeterData), otherMethodData(otherMethodData),
                         units(units)
                         {}
                         

    int getHoursPerDay() const { return hoursPerDay; }
    int getDaysPerMonth() const { return daysPerMonth; }
    int getMonthsPerYear() const { return monthsPerYear; }
    double getElectricityCost() const { return electricityCost; }
    int getMeasurementMethod() const { return measurementMethod; }
    int getUnits() const { return units; }
    MultimeterData getMultimeterData() const { return multimeterData; }
    NameplateData getNameplateData() const { return nameplateData; }
    PowerMeterData getPowerMeterData() const { return powerMeterData; }
    OtherMethodData getOtherMethodData() const { return otherMethodData; }


private:
    int hoursPerDay, daysPerMonth, monthsPerYear, measurementMethod, units;
    double electricityCost;
    MultimeterData multimeterData;
    NameplateData nameplateData;
    PowerMeterData powerMeterData;
    OtherMethodData otherMethodData;
};


class ElectricityReduction {
public:

    struct Output {
        Output(double energyUse, double energyCost, double annualEnergySavings, double costSavings, double power)
            : energyUse(energyUse), energyCost(energyCost), annualEnergySavings(annualEnergySavings), costSavings(costSavings), power(power)
            {
            }

        Output() = default;
        double energyUse = 0, energyCost = 0, annualEnergySavings = 0, costSavings = 0, power = 0;
    };

    ElectricityReduction(
        std::vector<ElectricityReductionInput> & electricityReductionInputVec
        ) :
            electricityReductionInputVec(electricityReductionInputVec)
    {
        // calculate();
    }

    ElectricityReduction::Output calculate();

    ElectricityReduction::Output calculate();
    ElectricityReduction::Output getOutput() { return output; }
    std::vector<ElectricityReductionInput> const & getElectricityReductionInputVec() const {
        return electricityReductionInputVec;
    }
    void setElectricityReductionInputVec(std::vector<ElectricityReductionInput> & electricityReductionInputVec);

private:
    std::vector<ElectricityReductionInput> electricityReductionInputVec;
    ElectricityReduction::Output output;
};




#endif // AMO_LIBRARY_ELECTRICITYREDUCTION_H