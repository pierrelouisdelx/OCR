static const int nInputs = 784;
static const int nHiddenNodes = 10; //To be updated
static const int nOutputs = 10;

double hiddenLayer[nHiddenNodes];
double outputLayer[nOutputs];

double hiddenLayerBias[nHiddenNodes];
double outputLayerBias[nOutputs];

double hiddenWeights[nInputs][nHiddenNodes];
double outputWeights[nHiddenNodes][nOutputs];

static const int epochs = 10;

