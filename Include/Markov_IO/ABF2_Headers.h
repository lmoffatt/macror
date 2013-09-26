#ifndef ABF2_HEADERS_H
#define ABF2_HEADERS_H


#include "Markov_LA/Matrix.h"
#include "Markov_IO/ABF1_Headers.h"


namespace Markov_IO
{

  // ABF 2.0 structures

  // All these structs are persisted to file -> their sizes must NOT be changed without careful
  // attention to versioning issues in order to maintain compatibility.

  struct ABF_Section
  {
     UINT     uBlockIndex;            // ABF block number of the first entry
     UINT     uBytes;                 // size in bytes of of each entry
     LONGLONG llNumEntries;           // number of entries in this section


  };

  struct ABF_FileInfo
  {
    char  uFileSignature[4];
    char  uFileVersionNumber[4];

     // After this point there is no need to be the same as the ABF 1 equivalent.
     UINT  uFileInfoSize;

     UINT  uActualEpisodes;
     UINT  uFileStartDate;
     UINT  uFileStartTimeMS;
     UINT  uStopwatchTime;
     short nFileType;
     short nDataFormat;
     short nSimultaneousScan;
     short nCRCEnable;
     UINT  uFileCRC;
     GUID  FileGUID;
     UINT  uCreatorVersion;
     UINT  uCreatorNameIndex;
     UINT  uModifierVersion;
     UINT  uModifierNameIndex;
     UINT  uProtocolPathIndex;

     // New sections in ABF 2 - protocol stuff ...
     ABF_Section ProtocolSection;           // the protocol
     ABF_Section ADCSection;                // one for each ADC channel
     ABF_Section DACSection;                // one for each DAC channel
     ABF_Section EpochSection;              // one for each epoch
     ABF_Section ADCPerDACSection;          // one for each ADC for each DAC
     ABF_Section EpochPerDACSection;        // one for each epoch for each DAC
     ABF_Section UserListSection;           // one for each user list
     ABF_Section StatsRegionSection;        // one for each stats region
     ABF_Section MathSection;
     ABF_Section StringsSection;

     // ABF 1 sections ...
     ABF_Section DataSection;            // Data
     ABF_Section TagSection;             // Tags
     ABF_Section ScopeSection;           // Scope config
     ABF_Section DeltaSection;           // Deltas
     ABF_Section VoiceTagSection;        // Voice Tags
     ABF_Section SynchArraySection;      // Synch Array
     ABF_Section AnnotationSection;      // Annotations
     ABF_Section StatsSection;           // Stats config

     char  sUnused[148];     // size = 512 bytes


  };

  struct ABF_ProtocolInfo
  {
     short nOperationMode;
     float fADCSequenceInterval;
     bool  bEnableFileCompression;
     char  sUnused1[3];
     UINT  uFileCompressionRatio;

     float fSynchTimeUnit;
     float fSecondsPerRun;
     int32_t  lNumSamplesPerEpisode;
     int32_t  lPreTriggerSamples;
     int32_t  lEpisodesPerRun;
     int32_t  lRunsPerTrial;
     int32_t  lNumberOfTrials;
     short nAveragingMode;
     short nUndoRunCount;
     short nFirstEpisodeInRun;
     float fTriggerThreshold;
     short nTriggerSource;
     short nTriggerAction;
     short nTriggerPolarity;
     float fScopeOutputInterval;
     float fEpisodeStartToStart;
     float fRunStartToStart;
     int32_t  lAverageCount;
     float fTrialStartToStart;
     short nAutoTriggerStrategy;
     float fFirstRunDelayS;

     short nChannelStatsStrategy;
     int32_t  lSamplesPerTrace;
     int32_t  lStartDisplayNum;
     int32_t  lFinishDisplayNum;
     short nShowPNRawData;
     float fStatisticsPeriod;
     int32_t  lStatisticsMeasurements;
     short nStatisticsSaveStrategy;

     float fADCRange;
     float fDACRange;
     int32_t  lADCResolution;
     int32_t  lDACResolution;

     short nExperimentType;
     short nManualInfoStrategy;
     short nCommentsEnable;
     int32_t  lFileCommentIndex;
     short nAutoAnalyseEnable;
     short nSignalType;

     short nDigitalEnable;
     short nActiveDACChannel;
     short nDigitalHolding;
     short nDigitalInterEpisode;
     short nDigitalDACChannel;
     short nDigitalTrainActiveLogic;

     short nStatsEnable;
     short nStatisticsClearStrategy;

     short nLevelHysteresis;
     int32_t  lTimeHysteresis;
     short nAllowExternalTags;
     short nAverageAlgorithm;
     float fAverageWeighting;
     short nUndoPromptStrategy;
     short nTrialTriggerSource;
     short nStatisticsDisplayStrategy;
     short nExternalTagType;
     short nScopeTriggerOut;

     short nLTPType;
     short nAlternateDACOutputState;
     short nAlternateDigitalOutputState;

     float fCellID[3];

     short nDigitizerADCs;
     short nDigitizerDACs;
     short nDigitizerTotalDigitalOuts;
     short nDigitizerSynchDigitalOuts;
     short nDigitizerType;

     char  sUnused[304];     // size = 512 bytes

   };

  struct ABF_MathInfo
  {
     short nMathEnable;
     short nMathExpression;
     UINT  uMathOperatorIndex;
     UINT  uMathUnitsIndex;
     float fMathUpperLimit;
     float fMathLowerLimit;
     short nMathADCNum[2];
     char  sUnused[16];
     float fMathK[6];

     char  sUnused2[64];     // size = 128 bytes

  };

  struct ABF_ADCInfo
  {
     // The ADC this struct is describing.
     short nADCNum;

     short nTelegraphEnable;
     short nTelegraphInstrument;
     float fTelegraphAdditGain;
     float fTelegraphFilter;
     float fTelegraphMembraneCap;
     short nTelegraphMode;
     float fTelegraphAccessResistance;

     short nADCPtoLChannelMap;
     short nADCSamplingSeq;

     float fADCProgrammableGain;
     float fADCDisplayAmplification;
     float fADCDisplayOffset;
     float fInstrumentScaleFactor;
     float fInstrumentOffset;
     float fSignalGain;
     float fSignalOffset;
     float fSignalLowpassFilter;
     float fSignalHighpassFilter;

     char  nLowpassFilterType;
     char  nHighpassFilterType;
     float fPostProcessLowpassFilter;
     char  nPostProcessLowpassFilterType;
     bool  bEnabledDuringPN;

     short nStatsChannelPolarity;

     uint32_t  lADCChannelNameIndex;
     uint32_t  lADCUnitsIndex;

     char  sUnused[46];         // size = 128 bytes

  };

  struct ABF_DACInfo
  {
     // The DAC this struct is describing.
     short nDACNum;

     short nTelegraphDACScaleFactorEnable;
     float fInstrumentHoldingLevel;

     float fDACScaleFactor;
     float fDACHoldingLevel;
     float fDACCalibrationFactor;
     float fDACCalibrationOffset;

     int32_t  lDACChannelNameIndex;
     int32_t  lDACChannelUnitsIndex;

     int32_t  lDACFilePtr;
     int32_t  lDACFileNumEpisodes;

     short nWaveformEnable;
     short nWaveformSource;
     short nInterEpisodeLevel;

     float fDACFileScale;
     float fDACFileOffset;
     int32_t  lDACFileEpisodeNum;
     short nDACFileADCNum;

     short nConditEnable;
     int32_t  lConditNumPulses;
     float fBaselineDuration;
     float fBaselineLevel;
     float fStepDuration;
     float fStepLevel;
     float fPostTrainPeriod;
     float fPostTrainLevel;
     short nMembTestEnable;

     short nLeakSubtractType;
     short nPNPolarity;
     float fPNHoldingLevel;
     short nPNNumADCChannels;
     short nPNPosition;
     short nPNNumPulses;
     float fPNSettlingTime;
     float fPNInterpulse;

     short nLTPUsageOfDAC;
     short nLTPPresynapticPulses;

     int32_t  lDACFilePathIndex;

     float fMembTestPreSettlingTimeMS;
     float fMembTestPostSettlingTimeMS;

     short nLeakSubtractADCIndex;

     char  sUnused[124];     // size = 256 bytes

    };

  struct ABF_EpochInfoPerDAC
  {
     // The Epoch / DAC this struct is describing.
     short nEpochNum;
     short nDACNum;

     // One full set of epochs (ABF_EPOCHCOUNT) for each DAC channel ...
     short nEpochType;
     float fEpochInitLevel;
     float fEpochLevelInc;
     long  lEpochInitDuration;
     long  lEpochDurationInc;
     long  lEpochPulsePeriod;
     long  lEpochPulseWidth;


     char  sUnused[18];      // size = 48 bytes

  };

  struct ABF_EpochInfo
  {
     // The Epoch this struct is describing.
     short nEpochNum;

     // Describes one epoch
     short nDigitalValue;
     short nDigitalTrainValue;
     short nAlternateDigitalValue;
     short nAlternateDigitalTrainValue;
     bool  bEpochCompression;   // Compress the data from this epoch using uFileCompressionRatio

     char  sUnused[21];      // size = 32 bytes

  };

  struct ABF_StatsRegionInfo
  {
     // The stats region this struct is describing.
     short nRegionNum;
     short nADCNum;

     short nStatsActiveChannels;
     short nStatsSearchRegionFlags;
     short nStatsSelectedRegion;
     short nStatsSmoothing;
     short nStatsSmoothingEnable;
     short nStatsBaseline;
     long  lStatsBaselineStart;
     long  lStatsBaselineEnd;

     // Describes one stats region
     long  lStatsMeasurements;
     long  lStatsStart;
     long  lStatsEnd;
     short nRiseBottomPercentile;
     short nRiseTopPercentile;
     short nDecayBottomPercentile;
     short nDecayTopPercentile;
     short nStatsSearchMode;
     short nStatsSearchDAC;
     short nStatsBaselineDAC;

     char  sUnused[78];   // size = 128 bytes

  };

  struct ABF_UserListInfo
  {
     // The user list this struct is describing.
     short nListNum;

     // Describes one user list
     short nULEnable;
     short nULParamToVary;
     short nULRepeat;
     long  lULParamValueListIndex;

     char  sUnused[52];   // size = 64 bytes

  };

}







#endif // ABF2_HEADERS_H
