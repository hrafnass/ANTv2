#include "measurement.h"

void Measurement::addTrial(Trial trial) { trial_values.push_back(trial); }
void Measurement::clearValues() { trial_values.clear(); }
vector<Trial> Measurement::getValues() { return trial_values; }
