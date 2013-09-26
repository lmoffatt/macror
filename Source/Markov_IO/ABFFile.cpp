#include "Markov_IO/ABFFile.h"
#include <fstream>
#include <cstdlib>
#include <cmath>

namespace Markov_IO
{

  bool ABFFile::isValid(const std::string path)
  {
    std::ifstream f;
    f.open(path.c_str(),std::ios::binary);
    char  H[3];

    f.read(&H[0],3);

    // is ABF file?
    if (H[0]=='A'&&H[1]=='B'&&H[2]=='F')
      return true;
    else return false;
  }


  double ABFFile::version()const
  {
    return ver_;
  }
  std::string ABFFile::protocol()const
  {
    return protocol_;

  }
  std::string ABFFile::dataFile()const
  {
    return dataFile_;
  }
  double ABFFile::dayCreated()const
  {
    return dayCreated_;
  }
  double ABFFile::timeCreated()const
  {
    return timeCreated_;
  }


  std::size_t ABFFile::nTotalSamples()const
  {
    return nTotalSamples_;
  }

  std::size_t ABFFile::nTrialsPerRun()const
  {
    return nTrialsPerRun_;

  }
  std::size_t ABFFile::nSweepsPerRun()const
  {
    return nSweepsPerRun_;
  }
  double ABFFile::sweepDuration()const
  {
    return sweepDuration_;
  }

  double ABFFile::SamplingRate()const
  {
    return SamplingRate_;
  }

  double ABFFile::timeBetweenRuns()const
  {
    return TrialStartToStart_;
  }

  double ABFFile::timeBetweenSweeps()const
  {
    return SweepStartToStart_;
  }

  const Markov_LA::M_Matrix<double>& ABFFile::t()
  {
    if (!inited_)
      init();
    return t_;
  }
  const Markov_LA::M_Matrix<double>& ABFFile::y(std::size_t channel)
  {
    if (!inited_)
      init();
    return y_[channel];
  }

  const Markov_LA::M_Matrix<double>& ABFFile::DAC(std::size_t channel)
  {
    if (!inited_)
      init();
    return DAC_[channel];
  }


  std::string ABFFile::AcquisitionMode()const
  {
    return AcquisitionMode_;
  }





  template <typename T>
  T ABFFile::getValuePos(char* H, uint32_t offset, std::string type)
  {

    if (type=="long")
      {
        int32_t* d;
        d=reinterpret_cast<int32_t*>(&H[offset]);
        T result=*d;
        return result;

      }

    else if (type=="short")
      {
        int16_t* d;
        d=reinterpret_cast<int16_t*>(&H[offset]);
        T result=*d;
        return result;
      }
    else if (type=="float")
      {
        float* d;
        d=reinterpret_cast<float*>(&H[offset]);

        T result=*d;
        return result;
      }
    else
      {
        return T();
      }

  }

  template <typename T>
  void ABFFile::getValuePos(T* result,char* H, int offset, std::string type,int nrep)
  {
    for (std::size_t i=0; i< nrep; i++)
      if (type=="short")
        result[i]=getValuePos<int16_t>(H,offset+i*2,type);
      else    if (type=="long")
        result[i]=getValuePos<int32_t>(H,offset+i*2,type);
      else    if (type=="float")
        result[i]=getValuePos<float>(H,offset+i*4,type);
      else
        result[i]=T();
  }


  std::string ABFFile::getStringPos(char* H,int offset,int length)
  {
    std::string result;
    for(int pos=offset; pos<offset+length; pos++)
      if(H[pos]!=0)
        result.push_back(H[pos]);
      else
        break;
    return result;

  }






  template<typename T>
  void extract(std::istream& s, T& data )
  {
    unsigned int n=sizeof(T);
    char c[sizeof(T)];
    s.read(&c[0],sizeof(T));
    data=*(reinterpret_cast<T*>(&c[0]));

  }





  template<typename T>
  void extract(std::istream& s, T& data, int n)
  {
    unsigned int k=sizeof(T);
    char *c=new char [k*n];
    s.read(c,k*n);
    for (std::size_t i=0; i<n; i++)
      *(&data+i)=*(reinterpret_cast<T*>(&c[i*k]));
    delete[] c;

  }
  template<>
  void extract(std::istream& s, std::string& data, int n )
  {
    char c[256];

    s.read(&c[0],n);
    data=std::string(c);
    //delete[] c;

  }

  template<>
  void extract(std::istream& s, ABFFileHeader& data)
  {
    // GROUP #1 - File ID and size information. (40 bytes)
    extract(s,data.lFileSignature[0],4);
    extract(s,data.fFileVersionNumber);
    extract(s,data.nOperationMode);
    extract(s,data.lActualAcqLength);
    extract(s,data.nNumPointsIgnored);
    extract(s,data.lActualEpisodes);
    extract(s,data.lFileStartDate);         // YYYYMMDD
    extract(s,data.lFileStartTime);
    extract(s,data.lStopwatchTime);
    extract(s,data.fHeaderVersionNumber);
    extract(s,data.nFileType);
    extract(s,data.nMSBinFormat);

    // GROUP #2 - File Structure (78 bytes)
    extract(s,data.lDataSectionPtr);
    extract(s,data.lTagSectionPtr);
    extract(s,data.lNumTagEntries);
    extract(s,data.lScopeConfigPtr);
    extract(s,data.lNumScopes);
    extract(s,data._lDACFilePtr);
    extract(s,data._lDACFileNumEpisodes);
    extract(s,data.sUnused001[0],4);
    extract(s,data.lDeltaArrayPtr);
    extract(s,data.lNumDeltas);
    extract(s,data.lVoiceTagPtr);
    extract(s,data.lVoiceTagEntries);
    extract(s,data.lUnused002);
    extract(s,data.lSynchArrayPtr);
    extract(s,data.lSynchArraySize);
    extract(s,data.nDataFormat);
    extract(s,data.nSimultaneousScan);
    extract(s,data.lStatisticsConfigPtr);
    extract(s,data.lAnnotationSectionPtr);
    extract(s,data.lNumAnnotations);
    extract(s,data.sUnused003[0],2);

    // GROUP #3 - Trial hierarchy information (82 bytes)
    /**
       The number of input channels we acquired.
       Do not access directly - use CABFHeader::get_channel_count_acquired
       */
    extract(s,data.channel_count_acquired);

    /**
       The number of input channels we recorded.
       Do not access directly - use CABFHeader::get_channel_count_recorded
       */
    extract(s,data.nADCNumChannels);
    extract(s,data.fADCSampleInterval);
    /*{{
          The documentation says these two sample intervals are the interval between multiplexed samples, but not all digitisers work like that.
          Instead, these are the per-channel sample rate divided by the number of channels.
          If the user chose 100uS and has two channels, this value will be 50uS.
          }}*/
    extract(s,data.fADCSecondSampleInterval);
    /*{{
          // The two sample intervals must be an integer multiple (or submultiple) of each other.
          if (fADCSampleInterval > fADCSecondSampleInterval)
             ASSERT(fmod(fADCSampleInterval, fADCSecondSampleInterval) == 0.0));
          if (fADCSecondSampleInterval, fADCSampleInterval)
             ASSERT(fmod(fADCSecondSampleInterval, fADCSampleInterval) == 0.0));
          }}*/
    extract(s,data.fSynchTimeUnit);
    extract(s,data.fSecondsPerRun);

    /**
       * The total number of samples per episode, for the recorded channels only.
       * This does not include channels which are acquired but not recorded.
       *
       * This is the number of samples per episode per channel, times the number of recorded channels.
       *
       * If you want the samples per episode for one channel, you must divide this by get_channel_count_recorded().
       */
    extract(s,data.lNumSamplesPerEpisode);
    extract(s,data.lPreTriggerSamples);
    extract(s,data.lEpisodesPerRun);
    extract(s,data.lRunsPerTrial);
    extract(s,data.lNumberOfTrials);
    extract(s,data.nAveragingMode);
    extract(s,data.nUndoRunCount);
    extract(s,data.nFirstEpisodeInRun);
    extract(s,data.fTriggerThreshold);
    extract(s,data.nTriggerSource);
    extract(s,data.nTriggerAction);
    extract(s,data.nTriggerPolarity);
    extract(s,data.fScopeOutputInterval);
    extract(s,data.fEpisodeStartToStart);
    extract(s,data.fRunStartToStart);
    extract(s,data.fTrialStartToStart);
    extract(s,data.lAverageCount);
    extract(s,data.lClockChange);
    extract(s,data.nAutoTriggerStrategy);

    // GROUP #4 - Display Parameters (44 bytes)
    extract(s,data.nDrawingStrategy);
    extract(s,data.nTiledDisplay);
    extract(s,data.nEraseStrategy);           // N.B. Discontinued. Use scope config entry instead.
    extract(s,data.nDataDisplayMode);
    extract(s,data.lDisplayAverageUpdate);
    extract(s,data.nChannelStatsStrategy);
    extract(s,data.lCalculationPeriod);       // N.B. Discontinued. Use fStatisticsPeriod.
    extract(s,data.lSamplesPerTrace);
    extract(s,data.lStartDisplayNum);
    extract(s,data.lFinishDisplayNum);
    extract(s,data.nMultiColor);
    extract(s,data.nShowPNRawData);
    extract(s,data.fStatisticsPeriod);
    extract(s,data.lStatisticsMeasurements);
    extract(s,data.nStatisticsSaveStrategy);

    // GROUP #5 - Hardware information (16 bytes)
    extract(s,data.fADCRange);
    extract(s,data.fDACRange);
    extract(s,data.lADCResolution);
    extract(s,data.lDACResolution);

    // GROUP #6 Environmental Information (118 bytes)
    extract(s,data.nExperimentType);
    extract(s,data._nAutosampleEnable);
    extract(s,data._nAutosampleADCNum);
    extract(s,data._nAutosampleInstrument);
    extract(s,data._fAutosampleAdditGain);
    extract(s,data._fAutosampleFilter);
    extract(s,data._fAutosampleMembraneCap);
    extract(s,data.nManualInfoStrategy);
    extract(s,data.fCellID1);
    extract(s,data.fCellID2);
    extract(s,data.fCellID3);
    extract(s,data.sCreatorInfo[0],ABF_CREATORINFOLEN);
    extract(s,data._sFileComment[0],ABF_OLDFILECOMMENTLEN);
    extract(s,data.nFileStartMillisecs);    // Milliseconds portion of lFileStartTime
    extract(s,data.nCommentsEnable);
    extract(s,data.sUnused003a[0],8);

    // GROUP #7 - Multi-channel information (1044 bytes)
    extract(s,data.nADCPtoLChannelMap[0],ABF_ADCCOUNT);
    extract(s,data.nADCSamplingSeq[0],ABF_ADCCOUNT);
    extract(s,data.sADCChannelName[0][0],ABF_ADCCOUNT*ABF_ADCNAMELEN);
    extract(s,data.sADCUnits[0][0],ABF_ADCCOUNT*ABF_ADCUNITLEN);
    extract(s,data.fADCProgrammableGain[0],ABF_ADCCOUNT);
    extract(s,data.fADCDisplayAmplification[0],ABF_ADCCOUNT);
    extract(s,data.fADCDisplayOffset[0],ABF_ADCCOUNT);
    extract(s,data.fInstrumentScaleFactor[0],ABF_ADCCOUNT);
    extract(s,data.fInstrumentOffset[0],ABF_ADCCOUNT);
    extract(s,data.fSignalGain[0],ABF_ADCCOUNT);
    extract(s,data.fSignalOffset[0],ABF_ADCCOUNT);
    extract(s,data.fSignalLowpassFilter[0],ABF_ADCCOUNT);
    extract(s,data.fSignalHighpassFilter[0],ABF_ADCCOUNT);
    extract(s,data.sDACChannelName[0][0],ABF_DACCOUNT*ABF_DACNAMELEN);
    extract(s,data.sDACChannelUnits[0][0],ABF_DACCOUNT*ABF_DACUNITLEN);
    extract(s,data.fDACScaleFactor[0],ABF_DACCOUNT);
    extract(s,data.fDACHoldingLevel[0],ABF_DACCOUNT);
    extract(s,data.nSignalType);
    extract(s,data.sUnused004[0],10);

    // GROUP #8 - Synchronous timer outputs (14 bytes)
    extract(s,data.nOUTEnable);
    extract(s,data.nSampleNumberOUT1);
    extract(s,data.nSampleNumberOUT2);
    extract(s,data.nFirstEpisodeOUT);
    extract(s,data.nLastEpisodeOUT);
    extract(s,data.nPulseSamplesOUT1);
    extract(s,data.nPulseSamplesOUT2);

    // GROUP #9 - Epoch Waveform and Pulses (184 bytes)
    extract(s,data.nDigitalEnable);
    extract(s,data._nWaveformSource);
    extract(s,data.nActiveDACChannel);
    extract(s,data._nInterEpisodeLevel);
    extract(s,data._nEpochType[0],ABF_EPOCHCOUNT);
    extract(s,data._fEpochInitLevel[0],ABF_EPOCHCOUNT);
    extract(s,data._fEpochLevelInc[0],ABF_EPOCHCOUNT);
    extract(s,data._nEpochInitDuration[0],ABF_EPOCHCOUNT);
    extract(s,data._nEpochDurationInc[0],ABF_EPOCHCOUNT);
    extract(s,data.nDigitalHolding);
    extract(s,data.nDigitalInterEpisode);
    extract(s,data.nDigitalValue[0],ABF_EPOCHCOUNT);
    extract(s,data.sUnavailable1608[0],4);    // was float fWaveformOffset);
    extract(s,data.nDigitalDACChannel);
    extract(s,data.sUnused005[0],6);

    // GROUP #10 - DAC Output File (98 bytes)
    extract(s,data._fDACFileScale);
    extract(s,data._fDACFileOffset);
    extract(s,data.sUnused006[0],2);
    extract(s,data._nDACFileEpisodeNum);
    extract(s,data._nDACFileADCNum);
    extract(s,data._sDACFilePath[0],ABF_DACFILEPATHLEN);

    // GROUP #11 - Presweep (conditioning) pulse train (44 bytes)
    extract(s,data._nConditEnable);
    extract(s,data._nConditChannel);
    extract(s,data._lConditNumPulses);
    extract(s,data._fBaselineDuration);
    extract(s,data._fBaselineLevel);
    extract(s,data._fStepDuration);
    extract(s,data._fStepLevel);
    extract(s,data._fPostTrainPeriod);
    extract(s,data._fPostTrainLevel);
    extract(s,data.sUnused007[0],12);

    // GROUP #12 - Variable parameter user list ( 82 bytes)
    extract(s,data._nParamToVary);
    extract(s,data._sParamValueList[0],ABF_VARPARAMLISTLEN);

    // GROUP #13 - Autopeak measurement (36 bytes)
    extract(s,data._nAutopeakEnable);
    extract(s,data._nAutopeakPolarity);
    extract(s,data._nAutopeakADCNum);
    extract(s,data._nAutopeakSearchMode);
    extract(s,data._lAutopeakStart);
    extract(s,data._lAutopeakEnd);
    extract(s,data._nAutopeakSmoothing);
    extract(s,data._nAutopeakBaseline);
    extract(s,data._nAutopeakAverage);
    extract(s,data.sUnavailable1866[0],2);     // Was nAutopeakSaveStrategy, use nStatisticsSaveStrategy
    extract(s,data._lAutopeakBaselineStart);
    extract(s,data._lAutopeakBaselineEnd);
    extract(s,data._lAutopeakMeasurements);

    // GROUP #14 - Channel Arithmetic (52 bytes)
    extract(s,data.nArithmeticEnable);
    extract(s,data.fArithmeticUpperLimit);
    extract(s,data.fArithmeticLowerLimit);
    extract(s,data.nArithmeticADCNumA);
    extract(s,data.nArithmeticADCNumB);
    extract(s,data.fArithmeticK1);
    extract(s,data.fArithmeticK2);
    extract(s,data.fArithmeticK3);
    extract(s,data.fArithmeticK4);
    extract(s,data.sArithmeticOperator[0],ABF_ARITHMETICOPLEN);
    extract(s,data.sArithmeticUnits[0],ABF_ARITHMETICUNITSLEN);
    extract(s,data.fArithmeticK5);
    extract(s,data.fArithmeticK6);
    extract(s,data.nArithmeticExpression);
    extract(s,data.sUnused008[0],2);

    // GROUP #15 - On-line subtraction (34 bytes)
    extract(s,data._nPNEnable);
    extract(s,data.nPNPosition);
    extract(s,data._nPNPolarity);
    extract(s,data.nPNNumPulses);
    extract(s,data._nPNADCNum);
    extract(s,data._fPNHoldingLevel);
    extract(s,data.fPNSettlingTime);
    extract(s,data.fPNInterpulse);
    extract(s,data.sUnused009[0],12);

    // GROUP #16 - Miscellaneous variables (82 bytes)
    extract(s,data._nListEnable);

    extract(s,data.nBellEnable[0],ABF_BELLCOUNT);
    extract(s,data.nBellLocation[0],ABF_BELLCOUNT);
    extract(s,data.nBellRepetitions[0],ABF_BELLCOUNT);

    extract(s,data.nLevelHysteresis);
    extract(s,data.lTimeHysteresis);
    extract(s,data.nAllowExternalTags);

    extract(s,data.nLowpassFilterType[0],ABF_ADCCOUNT);
    extract(s,data.nHighpassFilterType[0],ABF_ADCCOUNT);
    extract(s,data.nAverageAlgorithm);
    extract(s,data.fAverageWeighting);
    extract(s,data.nUndoPromptStrategy);
    extract(s,data.nTrialTriggerSource);
    extract(s,data.nStatisticsDisplayStrategy);
    extract(s,data.nExternalTagType);
    extract(s,data.lHeaderSize);
    extract(s,data.dFileDuration);
    extract(s,data.nStatisticsClearStrategy);
    // Size of v1.5 header = 2048

    // Extra parameters in v1.6
    // EXTENDED GROUP #2 - File Structure (26 bytes)
    extract(s,data.lDACFilePtr[0],ABF_WAVEFORMCOUNT);
    extract(s,data.lDACFileNumEpisodes[0],ABF_WAVEFORMCOUNT);
    extract(s,data.sUnused010[0],10);

    // EXTENDED GROUP #7 - Multi-channel information (62 bytes)
    extract(s,data.fDACCalibrationFactor[0],ABF_DACCOUNT);
    extract(s,data.fDACCalibrationOffset[0],ABF_DACCOUNT);
    extract(s,data.sUnused011[0],30);

    // GROUP #17 - Trains parameters (160 bytes)
    extract(s,data.lEpochPulsePeriod[0][0],ABF_WAVEFORMCOUNT*ABF_EPOCHCOUNT);
    extract(s,data.lEpochPulseWidth [0][0],ABF_WAVEFORMCOUNT*ABF_EPOCHCOUNT);

    // EXTENDED GROUP #9 - Epoch Waveform and Pulses ( 412 bytes)
    extract(s,data.nWaveformEnable[0],ABF_WAVEFORMCOUNT);
    extract(s,data.nWaveformSource[0],ABF_WAVEFORMCOUNT);
    extract(s,data.nInterEpisodeLevel[0],ABF_WAVEFORMCOUNT);
    extract(s,data.nEpochType[0][0],ABF_WAVEFORMCOUNT*ABF_EPOCHCOUNT);
    extract(s,data.fEpochInitLevel[0][0],ABF_WAVEFORMCOUNT*ABF_EPOCHCOUNT);
    extract(s,data.fEpochLevelInc[0][0],ABF_WAVEFORMCOUNT*ABF_EPOCHCOUNT);
    extract(s,data.lEpochInitDuration[0][0],ABF_WAVEFORMCOUNT*ABF_EPOCHCOUNT);
    extract(s,data.lEpochDurationInc[0][0],ABF_WAVEFORMCOUNT*ABF_EPOCHCOUNT);
    extract(s,data.nDigitalTrainValue[0],ABF_EPOCHCOUNT);                         // 2 * 10 = 20 bytes
    extract(s,data.nDigitalTrainActiveLogic);                                   // 2 bytes
    extract(s,data.sUnused012[0],18);

    // EXTENDED GROUP #10 - DAC Output File (552 bytes)
    extract(s,data.fDACFileScale[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fDACFileOffset[0],ABF_WAVEFORMCOUNT);
    extract(s,data.lDACFileEpisodeNum[0],ABF_WAVEFORMCOUNT);
    extract(s,data.nDACFileADCNum[0],ABF_WAVEFORMCOUNT);
    extract(s,data.sDACFilePath[0][0],ABF_WAVEFORMCOUNT*ABF_PATHLEN);
    extract(s,data.sUnused013[0],12);

    // EXTENDED GROUP #11 - Presweep (conditioning) pulse train (100 bytes)
    extract(s,data.nConditEnable[0],ABF_WAVEFORMCOUNT);
    extract(s,data.lConditNumPulses[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fBaselineDuration[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fBaselineLevel[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fStepDuration[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fStepLevel[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fPostTrainPeriod[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fPostTrainLevel[0],ABF_WAVEFORMCOUNT);
    extract(s,data.sUnused014[0],40);

    // EXTENDED GROUP #12 - Variable parameter user list (1096 bytes)
    extract(s,data.nULEnable[0],ABF_USERLISTCOUNT);
    extract(s,data.nULParamToVary[0],ABF_USERLISTCOUNT);
    extract(s,data.sULParamValueList[0][0],ABF_USERLISTCOUNT*ABF_USERLISTLEN);
    extract(s,data.nULRepeat[0],ABF_USERLISTCOUNT);
    extract(s,data.sUnused015[0],48);

    // EXTENDED GROUP #15 - On-line subtraction (56 bytes)
    extract(s,data.nPNEnable[0],ABF_WAVEFORMCOUNT);
    extract(s,data.nPNPolarity[0],ABF_WAVEFORMCOUNT);
    extract(s,data.nPNADCNum[0],ABF_WAVEFORMCOUNT);
    extract(s,data.fPNHoldingLevel[0],ABF_WAVEFORMCOUNT);
    extract(s,data.sUnused016[0],36);

    // EXTENDED GROUP #6 Environmental Information  (898 bytes)
    extract(s,data.nTelegraphEnable[0],ABF_ADCCOUNT);
    extract(s,data.nTelegraphInstrument[0],ABF_ADCCOUNT);
    extract(s,data.fTelegraphAdditGain[0],ABF_ADCCOUNT);
    extract(s,data.fTelegraphFilter[0],ABF_ADCCOUNT);
    extract(s,data.fTelegraphMembraneCap[0],ABF_ADCCOUNT);
    extract(s,data.nTelegraphMode[0],ABF_ADCCOUNT);
    extract(s,data.nTelegraphDACScaleFactorEnable[0],ABF_DACCOUNT);
    extract(s,data.sUnused016a[0],24);

    extract(s,data.nAutoAnalyseEnable);
    extract(s,data.sAutoAnalysisMacroName[0],ABF_MACRONAMELEN);
    extract(s,data.sProtocolPath[0],ABF_PATHLEN);

    extract(s,data.sFileComment[0],ABF_FILECOMMENTLEN);
    extract(s,data.sUnused017[0],128);

    // EXTENDED GROUP #13 - Statistics measurements (388 bytes)
    extract(s,data.nStatsEnable);
    extract(s,data.nStatsActiveChannels);             // Active stats channel bit flag
    extract(s,data.nStatsSearchRegionFlags);          // Active stats region bit flag
    extract(s,data.nStatsSelectedRegion);
    extract(s,data._nStatsSearchMode);
    extract(s,data.nStatsSmoothing);
    extract(s,data.nStatsSmoothingEnable);
    extract(s,data.nStatsBaseline);
    extract(s,data.lStatsBaselineStart);
    extract(s,data.lStatsBaselineEnd);
    extract(s,data.lStatsMeasurements[0],ABF_STATS_REGIONS);  // Measurement bit flag for each region
    extract(s,data.lStatsStart[0],ABF_STATS_REGIONS);
    extract(s,data.lStatsEnd[0],ABF_STATS_REGIONS);
    extract(s,data.nRiseBottomPercentile[0],ABF_STATS_REGIONS);
    extract(s,data.nRiseTopPercentile[0],ABF_STATS_REGIONS);
    extract(s,data.nDecayBottomPercentile[0],ABF_STATS_REGIONS);
    extract(s,data.nDecayTopPercentile[0],ABF_STATS_REGIONS);
    extract(s,data.nStatsChannelPolarity[0],ABF_ADCCOUNT);
    extract(s,data.nStatsSearchMode[0],ABF_STATS_REGIONS);    // Stats mode per region: mode is cursor region, epoch etc
    extract(s,data.sUnused018[0],156);

    // GROUP #18 - Application version data (16 bytes)
    extract(s,data.nMajorVersion);
    extract(s,data.nMinorVersion);
    extract(s,data.nBugfixVersion);
    extract(s,data.nBuildVersion);
    extract(s,data.sUnused019[0],8);

    // GROUP #19 - LTP protocol (14 bytes)
    extract(s,data.nLTPType);
    extract(s,data.nLTPUsageOfDAC[0],ABF_WAVEFORMCOUNT);
    extract(s,data.nLTPPresynapticPulses[0],ABF_WAVEFORMCOUNT);
    extract(s,data.sUnused020[0],4);

    // GROUP #20 - Digidata 132x Trigger out flag. (8 bytes)
    extract(s,data.nDD132xTriggerOut);
    extract(s,data.sUnused021[0],6);

    // GROUP #21 - Epoch resistance (40 bytes)
    extract(s,data.sEpochResistanceSignalName[0][0],ABF_WAVEFORMCOUNT*ABF_ADCNAMELEN);
    extract(s,data.nEpochResistanceState[0],ABF_WAVEFORMCOUNT);
    extract(s,data.sUnused022[0],16);

    // GROUP #22 - Alternating episodic mode (58 bytes)
    extract(s,data.nAlternateDACOutputState);
    extract(s,data.nAlternateDigitalValue[0],ABF_EPOCHCOUNT);
    extract(s,data.nAlternateDigitalTrainValue[0],ABF_EPOCHCOUNT);
    extract(s,data.nAlternateDigitalOutputState);
    extract(s,data.sUnused023[0],14);

    // GROUP #23 - Post-processing actions (210 bytes)
    extract(s,data.fPostProcessLowpassFilter[0],ABF_ADCCOUNT);
    extract(s,data.nPostProcessLowpassFilterType[0],ABF_ADCCOUNT);


    // 6014 header bytes allocated + 130 header bytes not allocated
    extract(s,data.sUnused2048[0],130);


  }




  template<>
  void extract(std::istream& s, ABF_FileInfo& data)
  {
    extract(s,data.uFileSignature[0],4);
    extract(s,data.uFileVersionNumber[0],4);


    // After this point there is no need to be the same as the ABF 1 equivalent.
    extract(s,data.uFileInfoSize);

    extract(s,data.uActualEpisodes);
    extract(s,data.uFileStartDate);
    extract(s,data.uFileStartTimeMS);
    extract(s,data.uStopwatchTime);
    extract(s,data.nFileType);
    extract(s,data.nDataFormat);
    extract(s,data.nSimultaneousScan);
    extract(s,data.nCRCEnable);
    extract(s,data.uFileCRC);
    extract(s,data.FileGUID);
    extract(s,data.uCreatorVersion);
    extract(s,data.uCreatorNameIndex);
    extract(s,data.uModifierVersion);
    extract(s,data.uModifierNameIndex);
    extract(s,data.uProtocolPathIndex);

    extract(s,data.ProtocolSection);
    extract(s,data.ADCSection);
    extract(s,data.DACSection);
    extract(s,data.EpochSection);
    extract(s,data.ADCPerDACSection);
    extract(s,data.EpochPerDACSection);
    extract(s,data.UserListSection);
    extract(s,data.StatsRegionSection);
    extract(s,data.MathSection);
    extract(s,data.StringsSection);

    extract(s,data.DataSection);
    extract(s,data.TagSection);
    extract(s,data.ScopeSection);
    extract(s,data.DeltaSection);
    extract(s,data.VoiceTagSection);
    extract(s,data.SynchArraySection);
    extract(s,data.AnnotationSection);
    extract(s,data.StatsSection);

  }




  template<>
  void extract(std::istream& s, ABF_ProtocolInfo& data)

  {
    extract(s,data.nOperationMode);

    extract(s,data.fADCSequenceInterval);
    extract(s,data.bEnableFileCompression);
    extract(s,data.sUnused1[0]);
    extract(s,data.sUnused1[1]);
    extract(s,data.sUnused1[2]);
    extract(s,data.uFileCompressionRatio);

    extract(s,data.fSynchTimeUnit);
    extract(s,data.fSecondsPerRun);
    extract(s,data.lNumSamplesPerEpisode);
    extract(s,data.lPreTriggerSamples);
    extract(s,data.lEpisodesPerRun);
    extract(s,data.lRunsPerTrial);
    extract(s,data.lNumberOfTrials);
    extract(s,data.nAveragingMode);
    extract(s,data.nUndoRunCount);
    extract(s,data.nFirstEpisodeInRun);
    extract(s,data.fTriggerThreshold);
    extract(s,data.nTriggerSource);
    extract(s,data.nTriggerAction);
    extract(s,data.nTriggerPolarity);
    extract(s,data.fScopeOutputInterval);
    extract(s,data.fEpisodeStartToStart);
    extract(s,data.fRunStartToStart);
    extract(s,data.lAverageCount);
    extract(s,data.fTrialStartToStart);
    extract(s,data.nAutoTriggerStrategy);
    extract(s,data.fFirstRunDelayS);

    extract(s,data.nChannelStatsStrategy);
    extract(s,data.lSamplesPerTrace);
    extract(s,data.lStartDisplayNum);
    extract(s,data.lFinishDisplayNum);
    extract(s,data.nShowPNRawData);
    extract(s,data.fStatisticsPeriod);
    extract(s,data.lStatisticsMeasurements);
    extract(s,data.nStatisticsSaveStrategy);

    extract(s,data.fADCRange);
    extract(s,data.fDACRange);
    extract(s,data.lADCResolution);
    extract(s,data.lDACResolution);

    extract(s,data.nExperimentType);
    extract(s,data.nManualInfoStrategy);
    extract(s,data.nCommentsEnable);
    extract(s,data.lFileCommentIndex);
    extract(s,data.nAutoAnalyseEnable);
    extract(s,data.nSignalType);

    extract(s,data.nDigitalEnable);
    extract(s,data.nActiveDACChannel);
    extract(s,data.nDigitalHolding);
    extract(s,data.nDigitalInterEpisode);
    extract(s,data.nDigitalDACChannel);
    extract(s,data.nDigitalTrainActiveLogic);

    extract(s,data.nStatsEnable);
    extract(s,data.nStatisticsClearStrategy);

    extract(s,data.nLevelHysteresis);
    extract(s,data.lTimeHysteresis);
    extract(s,data.nAllowExternalTags);
    extract(s,data.nAverageAlgorithm);
    extract(s,data.fAverageWeighting);
    extract(s,data.nUndoPromptStrategy);
    extract(s,data.nTrialTriggerSource);
    extract(s,data.nStatisticsDisplayStrategy);
    extract(s,data.nExternalTagType);
    extract(s,data.nScopeTriggerOut);

    extract(s,data.nLTPType);
    extract(s,data.nAlternateDACOutputState);
    extract(s,data.nAlternateDigitalOutputState);

    extract(s,data.fCellID[0],3);

    extract(s,data.nDigitizerADCs);
    extract(s,data.nDigitizerDACs);
    extract(s,data.nDigitizerTotalDigitalOuts);
    extract(s,data.nDigitizerSynchDigitalOuts);
    extract(s,data.nDigitizerType);
  }



  template<>
  void extract(std::istream& s, ABF_ADCInfo& data)

  {

    extract(s,data.nADCNum);

    extract(s,data.nTelegraphEnable);
    extract(s,data.nTelegraphInstrument);
    extract(s,data.fTelegraphAdditGain);
    extract(s,data.fTelegraphFilter);
    extract(s,data.fTelegraphMembraneCap);
    extract(s,data.nTelegraphMode);
    extract(s,data.fTelegraphAccessResistance);

    extract(s,data.nADCPtoLChannelMap);
    extract(s,data.nADCSamplingSeq);

    extract(s,data.fADCProgrammableGain);
    extract(s,data.fADCDisplayAmplification);
    extract(s,data.fADCDisplayOffset);
    extract(s,data.fInstrumentScaleFactor);
    extract(s,data.fInstrumentOffset);
    extract(s,data.fSignalGain);
    extract(s,data.fSignalOffset);
    extract(s,data.fSignalLowpassFilter);
    extract(s,data.fSignalHighpassFilter);

    extract(s,data.nLowpassFilterType);
    extract(s,data.nHighpassFilterType);
    extract(s,data.fPostProcessLowpassFilter);
    extract(s,data.nPostProcessLowpassFilterType);
    extract(s,data.bEnabledDuringPN);

    extract(s,data.nStatsChannelPolarity);

    extract(s,data.lADCChannelNameIndex);
    extract(s,data.lADCUnitsIndex);

    extract(s,data.sUnused[0],46);         // size = 128 bytes

  }


  template<>
  void extract(std::istream& s, ABF_DACInfo& data)
  {

    // The DAC this struct is describing.
    extract(s,data.nDACNum);

    extract(s,data.nTelegraphDACScaleFactorEnable);
    extract(s,data.fInstrumentHoldingLevel);

    extract(s,data.fDACScaleFactor);
    extract(s,data.fDACHoldingLevel);
    extract(s,data.fDACCalibrationFactor);
    extract(s,data.fDACCalibrationOffset);

    extract(s,data.lDACChannelNameIndex);
    extract(s,data.lDACChannelUnitsIndex);

    extract(s,data.lDACFilePtr);
    extract(s,data.lDACFileNumEpisodes);

    extract(s,data.nWaveformEnable);
    extract(s,data.nWaveformSource);
    extract(s,data.nInterEpisodeLevel);

    extract(s,data.fDACFileScale);
    extract(s,data.fDACFileOffset);
    extract(s,data.lDACFileEpisodeNum);
    extract(s,data.nDACFileADCNum);

    extract(s,data.nConditEnable);
    extract(s,data.lConditNumPulses);
    extract(s,data.fBaselineDuration);
    extract(s,data.fBaselineLevel);
    extract(s,data.fStepDuration);
    extract(s,data.fStepLevel);
    extract(s,data.fPostTrainPeriod);
    extract(s,data.fPostTrainLevel);
    extract(s,data.nMembTestEnable);

    extract(s,data.nLeakSubtractType);
    extract(s,data.nPNPolarity);
    extract(s,data.fPNHoldingLevel);
    extract(s,data.nPNNumADCChannels);
    extract(s,data.nPNPosition);
    extract(s,data.nPNNumPulses);
    extract(s,data.fPNSettlingTime);
    extract(s,data.fPNInterpulse);

    extract(s,data.nLTPUsageOfDAC);
    extract(s,data.nLTPPresynapticPulses);

    extract(s,data.lDACFilePathIndex);

    extract(s,data.fMembTestPreSettlingTimeMS);
    extract(s,data.fMembTestPostSettlingTimeMS);

    extract(s,data.nLeakSubtractADCIndex);

    extract(s,data.sUnused[124]);     // size = 256 bytes

  }











  ABFFile::ABFFile(const std::string& path):
    inited_(false),
    path_(path)
  {
    std::ifstream f;
    f.open(path.c_str(),std::ios::binary);
    char  H[6144];

    f.read(&H[0],6144);

    // is ABF file?
    if (H[0]=='A'&&H[1]=='B'&&H[2]=='F')
      {
        // signature of ABF2
        if (H[3]==32)
          {
            H1_=new ABFFileHeader;
            f.seekg(0);
            extract(f,*H1_);




            ver_=round(H1_->fFileVersionNumber*1000)/1000;
            protocol_=H1_->sProtocolPath;
            int pos=path.find_last_of("/\\");
            dataFile_=path.substr(pos+1);
            dayCreated_=H1_->lFileStartDate;
            timeCreated_=H1_->lFileStartTime;
            nTotalSamples_=H1_->lActualAcqLength;

            nTrialsPerRun_=H1_->lNumberOfTrials;
            nSweepsPerRun_=H1_->lEpisodesPerRun;

            sweepDuration_=H1_->fSecondsPerRun;

            nSignals_=H1_->nADCNumChannels;

            SamplingRate_=1e6/H1_->fADCSampleInterval;

            SampleInterval_=H1_->fADCSampleInterval;

            nTraceSamples_=H1_->lNumSamplesPerEpisode;

            TrialStartToStart_=H1_->fTrialStartToStart;
            SweepStartToStart_=H1_->fEpisodeStartToStart;

            AcquisitionMode_=H1_->nOperationMode;


            DAC_=std::vector<Markov_LA::M_Matrix<double> >(2);

            // this is used only for abf files






          }

        else if (H[3]=='2')
          {
            f.seekg(0);
            H2_=new ABF_FileInfo;
            extract(f,*H2_);

            HP_=std::vector<ABF_ProtocolInfo>(1);
            f.seekg(512*H2_[0].ProtocolSection.uBlockIndex);
            extract(f,HP_[0]);

            if(H2_->ADCSection.uBlockIndex>0)
              {
                std::size_t n=H2_->ADCSection.llNumEntries;

                HADC_=std::vector<ABF_ADCInfo>(n);
                for (std::size_t i=0; i<n; i++)
                  {
                    f.seekg(H2_->ADCSection.uBlockIndex*512+H2_->ADCSection.uBytes*i);
                    extract(f,HADC_[i]);
                  }
              }

            if(H2_->DACSection.uBlockIndex>0)
              {
                std::size_t n=H2_->DACSection.llNumEntries;

                HDAC_=std::vector<ABF_DACInfo>(n);
                for (std::size_t i=0; i<n; i++)
                  {
                    f.seekg(H2_->DACSection.uBlockIndex*512+H2_->DACSection.uBytes*i);
                    extract(f,HDAC_[i]);
                  }
              }
            if(H2_->EpochSection.uBlockIndex>0)
              {
                std::size_t n=H2_->EpochSection.llNumEntries;

                HEp_=std::vector<ABF_EpochInfo>(n);
                for (std::size_t i=0; i<n; i++)
                  {
                    f.seekg(H2_->EpochSection.uBlockIndex*512+H2_->EpochSection.uBytes*i);
                    extract(f,HEp_[i]);
                  }
              }

            if(H2_->StringsSection.uBlockIndex>0)
              {
                std::size_t n=H2_->StringsSection.llNumEntries;

                s2_=std::vector<std::string>(n);
                f.seekg(H2_->StringsSection.uBlockIndex*512);
                for (std::size_t i=0; i<n; i++)
                  {
                    std::string s;
                    while(s.empty())
                      getline(f,s,'\0');
                    s2_[i]=s;
                    if ((s=="Clampex")||(s=="Clampfit"))
                      iStrClampex_=i-H2_->uCreatorNameIndex;
                  }
              }




            ver_=H2_->uFileVersionNumber[3]+
                0.1*H2_->uFileVersionNumber[2]+
                0.01*H2_->uFileVersionNumber[1]+
                0.001*H2_->uFileVersionNumber[0];

            protocol_=s2_[H2_->uProtocolPathIndex+iStrClampex_];
            int pos=path.find_last_of("/\\");
            dataFile_=path.substr(pos+1);
            dayCreated_=H2_->uFileStartDate;
            timeCreated_=H2_->uFileStartTimeMS;
            nTotalSamples_=H2_->DataSection.llNumEntries;
            nSignals_=H2_->nSimultaneousScan; //or H2_->ADCSection.llNumEntries
            ABF_ProtocolInfo p=HP_[0];
            nTrialsPerRun_=p.lRunsPerTrial;
            nSweepsPerRun_=p.lNumberOfTrials;
            nTraceSamples_=nTotalSamples_/nSignals_/nSweepsPerRun_;
            sweepDuration_=p.fSecondsPerRun;
            TrialStartToStart_=p.fTrialStartToStart;
            SweepStartToStart_=p.fEpisodeStartToStart;
            ABF_ADCInfo a=HADC_[0];
            SamplingRate_=1.0e6/p.fADCSequenceInterval;



            AcquisitionMode_=p.nOperationMode;




            if (H2_->DataSection.uBlockIndex>0)
              {
                if (H2_->nDataFormat==0)
                  {
                    yScale_=std::vector<double> (nSignals_);
                    for (std::size_t n=0; n<nSignals_;n++)
                      {

                        ABF_ADCInfo a=HADC_[n];
                        yScale_[n]=p.fADCRange/p.lADCResolution/a.fInstrumentScaleFactor/
                            a.fSignalGain/a.fADCProgrammableGain/a.fTelegraphAdditGain;

                      }
                  }
              }



          }

       }
    else
      // not an ABF file
      {
        ver_=-1;
      }


  }

  void ABFFile::init()
  {
    build_y();
    build_DAC();
    build_t();
    inited_=true;
  }





  void ABFFile::build_y(){

    if (ver_<2.0)
      {

        if (this->dataFile().substr(dataFile().size()-3)=="abf")
          {
            y_=std::vector<Markov_LA::M_Matrix<double> >(nSignals_);

            //Getting the data
            std::ifstream f;
            f.open(path_.c_str(),std::ios::binary);

            f.seekg(512*H1_->lDataSectionPtr);
            if (H1_->nDataFormat==0)
              {
                std::vector<double> scale(nSignals_);
                for (std::size_t n=0; n<nSignals_; n++)
                  {
                    scale[n]=H1_->fADCRange/H1_->lADCResolution/H1_->fInstrumentScaleFactor[H1_->_nAutosampleADCNum]
                        /H1_->fSignalGain[H1_->_nAutosampleADCNum]/H1_->_fAutosampleAdditGain;
                    y_[n]=Markov_LA::M_Matrix<double>(nTraceSamples_,nSweepsPerRun_);
                  }
                for (std::size_t j=0; j<nSweepsPerRun_; ++j)
                  {
                    char * D=new char[nTraceSamples_*2*nSignals_];
                    f.read(D,nTraceSamples_*2*nSignals_);
                    for (int i=0; i< nTraceSamples_; i++)
                      {
                        for (std::size_t n=0; n<nSignals_;n++)
                          {
                            y_[n](i,j)=scale[n]*getValuePos<int16_t>(&D[0],(i*nSignals_+n)*2,"short");
                          }
                      }
                    delete[] D;
                  }
              }
            else if(H1_->nDataFormat==1)

              {
                for (std::size_t n=0; n<nSignals_; n++)
                  {

                    y_[n]=Markov_LA::M_Matrix<double>(nTraceSamples_,nSweepsPerRun_);
                  }
                for (std::size_t j=0; j<nSweepsPerRun_; ++j)
                  {

                    char * D=new char[nTraceSamples_*4*nSignals_];
                    f.read(D,nTraceSamples_*4*nSignals_);
                    for (int i=0; i< nTraceSamples_; i++)
                      for (std::size_t n=0; n<nSignals_;n++)
                        y_[n](i,j)=getValuePos<float>(&D[0],(i*nSignals_+n)*4,"float");

                    delete[] D;

                  }
              }
          }
      }
    else
      {
        y_=std::vector<Markov_LA::M_Matrix<double> >(nSignals_);



        if (H2_->DataSection.uBlockIndex>0)
          {
            std::ifstream f;
            f.open(path_.c_str(),std::ios::binary);
            f.seekg(512*H2_->DataSection.uBlockIndex);
            if (H2_->nDataFormat==0)
              {
                std::vector<double> scale(nSignals_);
                for (std::size_t n=0; n<nSignals_;n++)
                  {

                    y_[n]=Markov_LA::M_Matrix<double>(nTraceSamples_,nSweepsPerRun_);

                  }

                for (std::size_t j=0; j<nSweepsPerRun_; ++j)
                  {
                    char * D=new char[nTraceSamples_*2*nSignals_];
                    f.read(D,nTraceSamples_*2*nSignals_);
                    for (int i=0; i< nTraceSamples_; i++)
                      for (std::size_t n=0; n<nSignals_;n++)
                        y_[n](i,j)=yScale_[n]*getValuePos<int16_t>(&D[0],(i*nSignals_+n)*2,"short");

                    delete[] D;

                  }
              }
            else if(H2_->nDataFormat==1)
              {
                for (std::size_t n=0; n<nSignals_;n++)
                  {

                    y_[n]=Markov_LA::M_Matrix<double>(nTraceSamples_,nSweepsPerRun_);

                  }

                for (std::size_t j=0; j<nSweepsPerRun_; ++j)
                  {
                    char * D=new char[nTraceSamples_*4*nSignals_];
                    f.read(D,nTraceSamples_*4*nSignals_);
                    for (int i=0; i< nTraceSamples_; i++)
                      for (std::size_t n=0; n<nSignals_;n++)
                        y_[n](i,j)=getValuePos<float>(&D[0],(i*nSignals_+n)*4,"float");

                    delete[] D;

                  }
              }
          }

      }


  }
  void ABFFile::build_t(){

    //finding the time axis
    if (ver_<2)
      {
        t_=Markov_LA::M_Matrix<double>(this->nTraceSamples_,1);
        if (H1_->fADCSecondSampleInterval>0)
          {
            uint32_t clkchg;
            if (H1_->lClockChange==0)
              clkchg=H1_->lNumSamplesPerEpisode/2;
            else
              clkchg=H1_->lClockChange;
            for (std::size_t i=0; i<clkchg; i++)
              {
                t_(i,0)=1e-6*SampleInterval_*i;
              }
            for (std::size_t i=clkchg; i<nTraceSamples_; i++)
              {
                t_(i,0)=t_(clkchg-1,0)+1e-6*(i-clkchg)*H1_->fADCSecondSampleInterval;
              }
          }
        else
          for (std::size_t i=0; i<nTraceSamples_; i++)
            {
              t_(i,0)=1e-6*SampleInterval_*i;
            }

      }
    else
      {

        t_=Markov_LA::M_Matrix<double>(this->nTraceSamples_,1);
        for (std::size_t i=0; i<nTraceSamples_; i++)
          {
            t_(i,0)=1e-6*SampleInterval_*i;
          }

      }

  }
  void ABFFile::build_DAC()
  {
    //  %DAC data0

    if (ver_<2)
      {
        DAC_=std::vector<Markov_LA::M_Matrix<double> >(ABF_WAVEFORMCOUNT);

        for (std::size_t k=0; k<ABF_WAVEFORMCOUNT; k++)
          if (H1_->lDACFilePtr[k] !=0)
            {
              std::ifstream f;
              f.open(path_.c_str(),std::ios::binary);
              f.seekg(512*H1_->lDACFilePtr[k]);
              DAC_[k]=Markov_LA::M_Matrix<double>(nTraceSamples_,1);

              if (H1_->nDataFormat== 0)
                {

                  double scale=H1_->fDACRange/H1_->lDACResolution*H1_->fDACCalibrationFactor[k];
                  char * D=new char[nTraceSamples_*2];
                  if (f.read(D,nTraceSamples_))
                    for (int i=0; i< nTraceSamples_; i++)
                      {
                        double x=getValuePos<int16_t>(&D[0],i*2,"short");
                        DAC_[k](i,0)=scale*(H1_->fDACCalibrationOffset[k]+x);
                      }
                  delete[] D;

                }
              else if (H1_->nDataFormat==1)
                {
                  double scale=H1_->fDACRange/H1_->lDACResolution*H1_->fDACCalibrationFactor[k];
                  char * D=new char[nTraceSamples_*4];
                  if (f.read(D,nTraceSamples_*4))
                    for (int i=0; i<nTraceSamples_; i++)
                      DAC_[k](i,0)=scale*(H1_->fDACCalibrationOffset[k]+getValuePos<float>(&D[0],i*4,"float"));

                  delete[] D;

                }



            }
      }
    else
      {
        ABF_ProtocolInfo P=HP_[0];
        if(H2_->DACSection.uBlockIndex>0)
          {
            std::size_t n=H2_->DACSection.llNumEntries;
            DAC_=std::vector<Markov_LA::M_Matrix<double> >(n);


            for (std::size_t k=0; k<n; k++)
              {
                ABF_DACInfo DAC=HDAC_[k];

                if (DAC.lDACFilePtr!=0)
                  {
                    std::ifstream f;
                    f.open(path_.c_str(),std::ios::binary);
                    f.seekg(512*DAC.lDACFilePtr);
                    DAC_[k]=Markov_LA::M_Matrix<double>(nTraceSamples_,1);

                    if (H2_->nDataFormat== 0)
                      {

                        double scale=P.fDACRange/P.lDACResolution*DAC.fDACCalibrationFactor;
                        char * D=new char[nTraceSamples_*2];
                        f.read(D,nTraceSamples_);
                        for (int i=0; i< nTraceSamples_; i++)
                          DAC_[k](i,0)=scale*(DAC.fDACCalibrationOffset+getValuePos<int16_t>(&D[0],i*2,"short"));

                        delete[] D;

                      }
                    else if (H1_->nDataFormat==1)
                      {
                        double scale=P.fDACRange/P.lDACResolution*DAC.fDACCalibrationFactor;
                        char * D=new char[nTraceSamples_*4];
                        f.read(D,nTraceSamples_);
                        for (std::size_t i=0; i< nTraceSamples_; i++)
                          DAC_[k](i,0)=scale*(DAC.fDACCalibrationOffset+getValuePos<float>(&D[0],i*4,"float"));

                        delete[] D;

                      }



                  }


              }

          }



      }

  }
}
