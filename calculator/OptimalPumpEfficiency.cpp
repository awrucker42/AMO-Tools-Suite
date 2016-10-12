//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalPumpEfficiency.h"

double OptimalPumpEfficiency::calculate() {
    /*
     * DOUBLE_SUCTION
     */
    double jCoeff[5][2] = {{90.190375,     91.0},
                           {-7.8068742,    -3.6664629},
                           {0.00033366482, 0.0001264433},
                           {-8.1364684,    -14.697275},
                           {0.0026659434,  0.00072855045}};
    /*
     * VERTICAL_TURBINE
     */
    double vCoeff[5][3] = {{87.456119,     89.899894,     90.124016},
                           {-9.3556039,    -5.9800814,    -1.7332611},
                           {0.00067139092, 0.00019480643, 0.00014953651},
                           {-9.4309496,    -7.0638099,    -3.3197451},
                           {0.0039344122,  0.0010440162,  0.00015232542}};
    /*
     * LARGE_END_SUCTION
     */
    double gCoeff[5] = {90.379274,
                        -3.000737,
                        0.000034054964,
                        -4.818246,
                        0.00019083831};
    /*
     * END_SUCTION_ANSI_API
     */
    double fCoeff[5][2] = {{84.655455,    87.748473},
                           {-18.706336,   -7.6842423},
                           {0.0016056629, 0.0003739105},
                           {-20.655962,   -17.336122},
                           {0.0081197589, 0.0024096967}};
    /*
     * MULTISTAGE_BOILER_FEED
     */
    double eCoeff[5][2] = {{84.286574,    87.129684},
                           {-17.836167,   -7.8144274},
                           {0.0013236525, 0.00034998448},
                           {-26.951966,   -19.605637},
                           {0.0068256307, 0.0022387671}};
    /*
     * API_DOUBLE_SUCTION
     * and
     * END_SUCTION_STOCK
     */
    double dhCoeff[5][2] = {{87.199887,     90.158464},
                            {-10.580842,    -4.8350009},
                            {0.00027878405, 0.000048652395},
                            {-23.785033,    -7.2881572},
                            {0.0018831236,  0.00027630687}};
    /*
     * END_SUCTION_SUBMERSIBLE_SEWAGE
     * and
     * END_SUCTION_SEWAGE
     */
    double bcCoeff[5][2] = {{83.528143,     89.704526},
                            {-23.543231,    -6.9708815},
                            {0.00071315587, 0.000057096295},
                            {-37.584938,    -13.868089},
                            {0.005809375,   0.00046766436}};
    /*
     * END_SUCTION_SLURRY
     */
    double aCoeff[5][2] = {{79.096487,     85.957484},
                           {-32.006283,    -15.256678},
                           {0.00084199445, 0.00017627657},
                           {-23.100062,    -24.920847},
                           {0.0064912714,  0.0012055457}};

    /*
     * Below format has been kept to mimic the excel sheet. There must be a better way to do this.
     */
    double pumpEfficiency = 0.0;
    int range = 0;
    switch (style_) {
        case Pump::Style::DOUBLE_SUCTION:
            if (flowRate_ < 9000) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (jCoeff[0][range] + (jCoeff[1][range] * exp(-jCoeff[2][range] * flowRate_) +
                                                  jCoeff[3][range] * exp(-jCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::VERTICAL_TURBINE:
            if (flowRate_ < 2550) {
                range = 0;
            } else {
                if (flowRate_ < 7220) {
                    range = 1;
                } else {
                    range = 2;
                }
            }
            pumpEfficiency = (vCoeff[0][range] + (vCoeff[1][range] * exp(-vCoeff[2][range] * flowRate_) +
                                                  vCoeff[3][range] * exp(-vCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::LARGE_END_SUCTION:
            pumpEfficiency = (gCoeff[0] + (gCoeff[1] * exp(-gCoeff[2] * flowRate_) +
                                           gCoeff[3] * exp(-gCoeff[4] * flowRate_)));
            break;
        case Pump::Style::END_SUCTION_ANSI_API:
            if (flowRate_ < 1030) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (fCoeff[0][range] + (fCoeff[1][range] * exp(-fCoeff[2][range] * flowRate_) +
                                                  fCoeff[3][range] * exp(-fCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::MULTISTAGE_BOILER_FEED:
            if (flowRate_ < 890) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (eCoeff[0][range] + (eCoeff[1][range] * exp(-eCoeff[2][range] * flowRate_) +
                                                  eCoeff[3][range] * exp(-eCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::END_SUCTION_STOCK:
            if (flowRate_ < 4440) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (dhCoeff[0][range] + (dhCoeff[1][range] * exp(-dhCoeff[2][range] * flowRate_) +
                                                   dhCoeff[3][range] * exp(-dhCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::API_DOUBLE_SUCTION:
            //same as Pump::Style::END_SUCTION_STOCK
            if (flowRate_ < 4440) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (dhCoeff[0][range] + (dhCoeff[1][range] * exp(-dhCoeff[2][range] * flowRate_) +
                                                   dhCoeff[3][range] * exp(-dhCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::END_SUCTION_SEWAGE:
            if (flowRate_ < 2170) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (bcCoeff[0][range] + (bcCoeff[1][range] * exp(-bcCoeff[2][range] * flowRate_) +
                                                   bcCoeff[3][range] * exp(-bcCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE:
            //same as Pump::Style::END_SUCTION_SEWAGE
            if (flowRate_ < 2170) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (bcCoeff[0][range] + (bcCoeff[1][range] * exp(-bcCoeff[2][range] * flowRate_) +
                                                   bcCoeff[3][range] * exp(-bcCoeff[4][range] * flowRate_)));

            break;
        case Pump::Style::END_SUCTION_SLURRY:
            if (flowRate_ < 1690) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (aCoeff[0][range] + (aCoeff[1][range] * exp(-aCoeff[2][range] * flowRate_) +
                                                  aCoeff[3][range] * exp(-aCoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY:

            break;
    }
    /*
     * You may have individual functions for each also.
     */
    /*
     * Viscosity Correction Factor
     */
    double parameterB =
            26.6 * (pow(kinematicViscosity_, 0.5) * pow(head_, 0.0625)) / (pow(flowRate_, 0.375) * pow(rpm_, 0.25));
    double viscosityCorrectionFactor = std::fmin(1, (pow(parameterB, -(0.0547 * pow(parameterB, 0.69)))));
    /*
     * Speed Correction
     */
    double notVTP[7][2] = {{14.884085,           6.5703317},
                           {-0.021342141,        -0.010048327},
                           {0.0000121172,        0.0000061475098},
                           {-0.0000000031885957, -0.0000000019659725},
                           {1.4907927E-13,       3.5079978E-13},
                           {1.2855352E-16,       -3.2272033E-17},
                           {-2.3798184E-20,      1.1881188E-21}};

    double VTP[7][2] = {{14.788539,           4.0559384},
                        {-0.022490348,        -0.0026632249},
                        {0.000017226359,      0.0000006761157},
                        {-0.0000000075690542, -0.000000000087766773},
                        {1.8893534E-12,       6.5103425E-15},
                        {-2.4834106E-16,      -2.5380141E-19},
                        {1.3345507E-20,       4.007753E-24}};
    double specificSpeed = rpm_ * sqrt(flowRate_) / (pow((head_ / stageCount_), 0.75));
    double speedCorrection = 0;
    int speedCoeffChooser = 0;
    if (style_ == Pump::Style::VERTICAL_TURBINE) {
        if (specificSpeed < 4550)
            speedCoeffChooser = 0;
        else
            speedCoeffChooser = 1;
        speedCorrection = std::fmax((VTP[0][speedCoeffChooser] + (VTP[1][speedCoeffChooser] * specificSpeed) +
                                     (VTP[2][speedCoeffChooser] * pow(specificSpeed, 2)) +
                                     (VTP[3][speedCoeffChooser] * pow(specificSpeed, 3)) +
                                     (VTP[4][speedCoeffChooser] * pow(specificSpeed, 4)) +
                                     (VTP[5][speedCoeffChooser] * pow(specificSpeed, 5)) +
                                     (VTP[6][speedCoeffChooser] * pow(specificSpeed, 6))), 0) / 100;
    } else {
        if (specificSpeed < 2530)
            speedCoeffChooser = 0;
        else
            speedCoeffChooser = 1;
        speedCorrection = std::fmax((notVTP[0][speedCoeffChooser] + (notVTP[1][speedCoeffChooser] * specificSpeed) +
                                     (notVTP[2][speedCoeffChooser] * pow(specificSpeed, 2)) +
                                     (notVTP[3][speedCoeffChooser] * pow(specificSpeed, 3)) +
                                     (notVTP[4][speedCoeffChooser] * pow(specificSpeed, 4)) +
                                     (notVTP[5][speedCoeffChooser] * pow(specificSpeed, 5)) +
                                     (notVTP[6][speedCoeffChooser] * pow(specificSpeed, 6))), 0) / 100;
    }

    /*
     * positiveDeviationFactor
     */
    double pdCoeff[5] = {0.10805906,
                         18.077243,
                         0.78231304,
                         30.525232,
                         0.80684022};
    double positiveDeviationFactor =
            1 + (pdCoeff[0] + (pdCoeff[1] * exp(-pdCoeff[2] * log(flowRate_))) +
                 pdCoeff[3] * exp(-pdCoeff[4] * log(flowRate_))) / 100;
    /*
     * Optimal Efficiency
     */
    optimalEfficiency_ = (pumpEfficiency * viscosityCorrectionFactor - speedCorrection) * positiveDeviationFactor;
    return optimalEfficiency_;
}
