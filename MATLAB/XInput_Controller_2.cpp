/*
 * File: XInput_Controller_2.cpp
 *
 *
 *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
 *
 *   This file is an S-function produced by the S-Function
 *   Builder which only recognizes certain fields.  Changes made
 *   outside these fields will be lost the next time the block is
 *   used to load, edit, and resave this file. This file will be overwritten
 *   by the S-function Builder block. If you want to edit this file by hand,
 *   you must change it only in the area defined as:
 *
 *        %%%-SFUNWIZ_defines_Changes_BEGIN
 *        #define NAME 'replacement text'
 *        %%% SFUNWIZ_defines_Changes_END
 *
 *   DO NOT change NAME--Change the 'replacement text' only.
 *
 *   For better compatibility with the Simulink Coder, the
 *   "wrapper" S-function technique is used.  This is discussed
 *   in the Simulink Coder's Manual in the Chapter titled,
 *   "Wrapper S-functions".
 *
 *  -------------------------------------------------------------------------
 * | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
 *  -------------------------------------------------------------------------
 *
 * Created: Tue Apr 04 10:16:57 2023
 */

#define S_FUNCTION_LEVEL               2
#define S_FUNCTION_NAME                XInput_Controller_2

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/* %%%-SFUNWIZ_defines_Changes_BEGIN --- EDIT HERE TO _END */
#define NUM_INPUTS                     0
#define NUM_OUTPUTS                    3

/* Output Port  0 */
#define OUT_PORT_0_NAME                axes
#define OUTPUT_0_DIMS_ND               {6,1}
#define OUTPUT_0_NUM_ELEMS             6
#define OUTPUT_0_WIDTH                 6
#define OUTPUT_DIMS_0_COL              1
#define OUTPUT_0_DTYPE                 real_T
#define OUTPUT_0_COMPLEX               COMPLEX_NO
#define OUT_0_BUS_BASED                0
#define OUT_0_BUS_NAME
#define OUT_0_DIMS                     1-D
#define OUT_0_ISSIGNED                 1
#define OUT_0_WORDLENGTH               8
#define OUT_0_FIXPOINTSCALING          1
#define OUT_0_FRACTIONLENGTH           3
#define OUT_0_BIAS                     0
#define OUT_0_SLOPE                    0.125

/* Output Port  1 */
#define OUT_PORT_1_NAME                buttons
#define OUTPUT_1_DIMS_ND               {14,1}
#define OUTPUT_1_NUM_ELEMS             14
#define OUTPUT_1_WIDTH                 14
#define OUTPUT_DIMS_1_COL              1
#define OUTPUT_1_DTYPE                 real_T
#define OUTPUT_1_COMPLEX               COMPLEX_NO
#define OUT_1_BUS_BASED                0
#define OUT_1_BUS_NAME
#define OUT_1_DIMS                     1-D
#define OUT_1_ISSIGNED                 1
#define OUT_1_WORDLENGTH               8
#define OUT_1_FIXPOINTSCALING          1
#define OUT_1_FRACTIONLENGTH           3
#define OUT_1_BIAS                     0
#define OUT_1_SLOPE                    0.125

/* Output Port  2 */
#define OUT_PORT_2_NAME                info
#define OUTPUT_2_DIMS_ND               {3,1}
#define OUTPUT_2_NUM_ELEMS             3
#define OUTPUT_2_WIDTH                 3
#define OUTPUT_DIMS_2_COL              1
#define OUTPUT_2_DTYPE                 real_T
#define OUTPUT_2_COMPLEX               COMPLEX_NO
#define OUT_2_BUS_BASED                0
#define OUT_2_BUS_NAME
#define OUT_2_DIMS                     1-D
#define OUT_2_ISSIGNED                 1
#define OUT_2_WORDLENGTH               8
#define OUT_2_FIXPOINTSCALING          1
#define OUT_2_FRACTIONLENGTH           3
#define OUT_2_BIAS                     0
#define OUT_2_SLOPE                    0.125
#define NPARAMS                        1

/* Parameter 0 */
#define PARAMETER_0_NAME               Controller_ID
#define PARAMETER_0_DTYPE              real_T
#define PARAMETER_0_COMPLEX            COMPLEX_NO
#define SAMPLE_TIME_0                  INHERITED_SAMPLE_TIME
#define NUM_DISC_STATES                0
#define DISC_STATES_IC                 [0]
#define NUM_CONT_STATES                0
#define CONT_STATES_IC                 [0]
#define SFUNWIZ_GENERATE_TLC           1
#define SOURCEFILES                    "__SFB__"
#define PANELINDEX                     N/A
#define USE_SIMSTRUCT                  0
#define SHOW_COMPILE_STEPS             0
#define CREATE_DEBUG_MEXFILE           0
#define SAVE_CODE_ONLY                 0
#define SFUNWIZ_REVISION               3.0

/* %%%-SFUNWIZ_defines_Changes_END --- EDIT HERE TO _BEGIN */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "simstruc.h"
#define PARAM_DEF0(S)                  ssGetSFcnParam(S, 0)
#define IS_PARAM_DOUBLE(pVal)          (mxIsNumeric(pVal) && !mxIsLogical(pVal) &&\
!mxIsEmpty(pVal) && !mxIsSparse(pVal) && !mxIsComplex(pVal) && mxIsDouble(pVal))

extern void XInput_Controller_2_Outputs_wrapper(real_T *axes,
  real_T *buttons,
  real_T *info,
  const real_T *Controller_ID, const int_T p_width0);
extern void XInput_Controller_2_Terminate_wrapper(const real_T *Controller_ID,
  const int_T p_width0);

/*====================*
 * S-function methods *
 *====================*/
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)

/* Function: mdlCheckParameters =============================================
 * Abstract:
 *     Verify parameter definitions and types.
 */
static void mdlCheckParameters(SimStruct *S)
{
  int paramIndex = 0;
  bool invalidParam = false;

  /* All parameters must match the S-function Builder Dialog */
  {
    const mxArray *pVal0 = ssGetSFcnParam(S, 0);
    if (!IS_PARAM_DOUBLE(pVal0)) {
      invalidParam = true;
      paramIndex = 0;
      goto EXIT_POINT;
    }
  }

 EXIT_POINT:
  if (invalidParam) {
    static char parameterErrorMsg[1024];
    sprintf(parameterErrorMsg,
            "The data type and or complexity of parameter %d does not match the "
            "information specified in the S-function Builder dialog. "
            "For non-double parameters you will need to cast them using int8, int16, "
            "int32, uint8, uint16, uint32 or boolean.", paramIndex + 1);
    ssSetLocalErrorStatus(S, parameterErrorMsg);
  }

  return;
}

#endif                                 /* MDL_CHECK_PARAMETERS */

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{
  DECL_AND_INIT_DIMSINFO(outputDimsInfo);
  ssSetNumSFcnParams(S, NPARAMS);      /* Number of expected parameters */

#if defined(MATLAB_MEX_FILE)

  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {
    mdlCheckParameters(S);
    if (ssGetErrorStatus(S) != NULL) {
      return;
    }
  } else {
    return;                            /* Parameter mismatch will be reported by Simulink */
  }

#endif

  ssSetArrayLayoutForCodeGen(S, SS_COLUMN_MAJOR);
  ssSetOperatingPointCompliance(S, USE_DEFAULT_OPERATING_POINT);
  ssSetNumContStates(S, NUM_CONT_STATES);
  ssSetNumDiscStates(S, NUM_DISC_STATES);
  if (!ssSetNumInputPorts(S, NUM_INPUTS))
    return;
  if (!ssSetNumOutputPorts(S, NUM_OUTPUTS))
    return;

  /* Output Port 0 */
  ssSetOutputPortWidth(S, 0, OUTPUT_0_NUM_ELEMS);
  ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);

  /* Output Port 1 */
  ssSetOutputPortWidth(S, 1, OUTPUT_1_NUM_ELEMS);
  ssSetOutputPortDataType(S, 1, SS_DOUBLE);
  ssSetOutputPortComplexSignal(S, 1, OUTPUT_1_COMPLEX);

  /* Output Port 2 */
  ssSetOutputPortWidth(S, 2, OUTPUT_2_NUM_ELEMS);
  ssSetOutputPortDataType(S, 2, SS_DOUBLE);
  ssSetOutputPortComplexSignal(S, 2, OUTPUT_2_COMPLEX);
  ssSetNumPWork(S, 0);
  ssSetNumSampleTimes(S, 1);
  ssSetNumRWork(S, 0);
  ssSetNumIWork(S, 0);
  ssSetNumModes(S, 0);
  ssSetNumNonsampledZCs(S, 0);
  ssSetSimulinkVersionGeneratedIn(S, "10.6");

  /* Take care when specifying exception free code - see sfuntmpl_doc.c */
  ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                   SS_OPTION_USE_TLC_WITH_ACCELERATOR |
                   SS_OPTION_WORKS_WITH_CODE_REUSE));
}

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO

static void mdlSetInputPortDimensionInfo(SimStruct *S,
  int_T port,
  const DimsInfo_T *dimsInfo)
{
  if (!ssSetInputPortDimensionInfo(S, port, dimsInfo))
    return;
}

#endif

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO)

static void mdlSetOutputPortDimensionInfo(SimStruct *S,
  int_T port,
  const DimsInfo_T *dimsInfo)
{
  if (!ssSetOutputPortDimensionInfo(S, port, dimsInfo))
    return;
}

#endif

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO

static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
  DECL_AND_INIT_DIMSINFO(portDimsInfo);
  int_T dims[2];

  /* Setting default dimensions for output port 0 */
  portDimsInfo.width = OUTPUT_0_NUM_ELEMS;
  dims[0] = OUTPUT_0_NUM_ELEMS;
  dims[1] = 1;
  portDimsInfo.numDims = 2;
  if (ssGetOutputPortNumDimensions(S, 0) == (-1)) {
    ssSetOutputPortDimensionInfo(S, 0, &portDimsInfo);
  }

  /* Setting default dimensions for output port 1 */
  portDimsInfo.width = OUTPUT_1_NUM_ELEMS;
  dims[0] = OUTPUT_1_NUM_ELEMS;
  dims[1] = 1;
  portDimsInfo.numDims = 2;
  if (ssGetOutputPortNumDimensions(S, 1) == (-1)) {
    ssSetOutputPortDimensionInfo(S, 1, &portDimsInfo);
  }

  /* Setting default dimensions for output port 2 */
  portDimsInfo.width = OUTPUT_2_NUM_ELEMS;
  dims[0] = OUTPUT_2_NUM_ELEMS;
  dims[1] = 1;
  portDimsInfo.numDims = 2;
  if (ssGetOutputPortNumDimensions(S, 2) == (-1)) {
    ssSetOutputPortDimensionInfo(S, 2, &portDimsInfo);
  }

  return;
}

/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  ssSetSampleTime(S, 0, SAMPLE_TIME_0);
  ssSetModelReferenceSampleTimeDefaultInheritance(S);
  ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_SET_OUTPUT_PORT_DATA_TYPE

static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
  ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES

static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
  ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}

#define MDL_SET_WORK_WIDTHS
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)

static void mdlSetWorkWidths(SimStruct *S)
{
  const char_T *rtParamNames[] = { "P1" };

  ssRegAllTunableParamsAsRunTimeParams(S, rtParamNames);
}

#endif

#define MDL_START                                                /* Change to #undef to remove function */
#if defined(MDL_START)

/* Function: mdlStart =======================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
static void mdlStart(SimStruct *S)
{
}

#endif                                 /*  MDL_START */

/* Function: mdlOutputs =======================================================
 *
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  real_T *axes = (real_T *) ssGetOutputPortRealSignal(S, 0);
  real_T *buttons = (real_T *) ssGetOutputPortRealSignal(S, 1);
  real_T *info = (real_T *) ssGetOutputPortRealSignal(S, 2);
  const int_T p_width0 = mxGetNumberOfElements(PARAM_DEF0(S));
  const real_T *Controller_ID = (const real_T *) mxGetData(PARAM_DEF0(S));
  XInput_Controller_2_Outputs_wrapper(axes, buttons, info, Controller_ID,
    p_width0);
}

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
  const int_T p_width0 = mxGetNumberOfElements(PARAM_DEF0(S));
  const real_T *Controller_ID = (const real_T *) mxGetData(PARAM_DEF0(S));
  XInput_Controller_2_Terminate_wrapper(Controller_ID, p_width0);
}

#ifdef MATLAB_MEX_FILE                 /* Is this file being compiled as a MEX-file? */
#include "simulink.c"                  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"                   /* Code generation registration function */
#endif
