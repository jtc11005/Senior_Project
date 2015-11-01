#include "Motor.h"

//#define ntaps 151
#define blocksize 1

//float32_t fcoef[ntaps] = {0.000002, 0.000004, 0.000007, 0.000011, 0.000016, 0.000022, 0.000030, 0.000040, 0.000050, 0.000062, 0.000075, 0.000089, 0.000102, 0.000114, 0.000125, 0.000133, 0.000136, 0.000134, 0.000124, 0.000105, 0.000076, 0.000034, -0.000022, -0.000094, -0.000183, -0.000290, -0.000416, -0.000560, -0.000723, -0.000903, -0.001099, -0.001307, -0.001525, -0.001748, -0.001970, -0.002185, -0.002386, -0.002565, -0.002713, -0.002821, -0.002878, -0.002875, -0.002801, -0.002646, -0.002399, -0.002050, -0.001593, -0.001017, -0.000318, 0.000510, 0.001471, 0.002564, 0.003790, 0.005144, 0.006622, 0.008216, 0.009915, 0.011707, 0.013576, 0.015506, 0.017479, 0.019473, 0.021467, 0.023438, 0.025363, 0.027220, 0.028983, 0.030631, 0.032143, 0.033498, 0.034677, 0.035666, 0.036449, 0.037017, 0.037360, 0.037476, 0.037360, 0.037017, 0.036449, 0.035666, 0.034677, 0.033498, 0.032143, 0.030631, 0.028983, 0.027220, 0.025363, 0.023438, 0.021467, 0.019473, 0.017479, 0.015506, 0.013576, 0.011707, 0.009915, 0.008216, 0.006622, 0.005144, 0.003790, 0.002564, 0.001471, 0.000510, -0.000318, -0.001017, -0.001593, -0.002050, -0.002399, -0.002646, -0.002801, -0.002875, -0.002878, -0.002821, -0.002713, -0.002565, -0.002386, -0.002185, -0.001970, -0.001748, -0.001525, -0.001307, -0.001099, -0.000903, -0.000723, -0.000560, -0.000416, -0.000290, -0.000183, -0.000094, -0.000022, 0.000034, 0.000076, 0.000105, 0.000124, 0.000134, 0.000136, 0.000133, 0.000125, 0.000114, 0.000102, 0.000089, 0.000075, 0.000062, 0.000050, 0.000040, 0.000030, 0.000022, 0.000016, 0.000011, 0.000007, 0.000004, 0.000002};
//float32_t pstate[ntaps + blocksize - 1];	
//float32_t input[blocksize];
//float32_t output[blocksize];
//int count = 0;
//arm_fir_instance_f32 filter;

#define numStages 2

float32_t standard_coeffs [5 * numStages] = {
	0.0001,   -0.0002,    0.0001,   -1.9599,    0.9605,
    1.0000,   -1.9628,    1.0000,   -1.9826,    0.9839};
//q31_t pCoeffs [5 * 2];
//q63_t pState [4 * 2];
//uint8_t postShift = 0;
//arm_biquad_cas_df1_32x64_ins_q31 filter;
float32_t pState[2*numStages];

void Motor_init(
	struct Motor *M,
	float No_Load_Current,
	float No_Load_Rpm,
	float Stall_Current,
	float Resistance) {
		
		// COPY INPUT ARGUMENTS TO STRUCT DATA
		M->No_Load_Current = No_Load_Current;
		M->No_Load_Rpm = No_Load_Rpm;
		M->Stall_Current = Stall_Current;
		M->Resistance = Resistance;
		
		// INTIALIZE SPEED DATA VALUES
		M->BEMF_Speed = 0;
		M->Encoder_Speed = 0;
		M->Desired_Speed = 0;
		
		// INITIALIZED IIR FILTER FOR CURRENT SENSING
		arm_biquad_cascade_df2T_init_f32(&M->filter, numStages, standard_coeffs, M->pState); 
	
	}
	
void Motor_PID_init(
	struct Motor *M,
	float iGain,
	float pGain,
	float dGain) {
		
		// PASS PARAMETERS TO STRUCT
		M->iGain = iGain;
		M->pGain = pGain;
		M->dGain = dGain;
		
		
		
		
		
	}
	