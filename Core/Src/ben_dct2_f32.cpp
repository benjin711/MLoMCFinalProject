#include "ben_dct2_f32.h"
#include <arm_math.h>

void ben_dct2_f32(float32_t* pInlineBuffer, float32_t* pState, float32_t* mfcc_out, arm_rfft_fast_instance_f32* pRfft){
	const uint16_t N = 64;
	const uint16_t Nby2 = 32;
	const float32_t normalize = 0.17677669529663689; // sqrt(2/N)

	// Big precalculated coefficients table (or multipy by 2?)
	float32_t Weights_64[128]=
	{
			0.5, 0.0, 0.4998494093481021, -0.012270614261456144, 0.4993977281025862, -0.024533837163709007, 0.4986452283393451, -0.03678228179983371,
			0.49759236333609846, -0.0490085701647803, 0.496239767299355, -0.0612053375996081, 0.4945882549823905, -0.07336523722768087, 0.4926388211944706, -0.08548094438015061,
			0.4903926402016152, -0.09754516100806412, 0.4878510650192643, -0.1095506200784349, 0.485015626597272, -0.12149008995163194, 0.4818880328977199, -0.13335637873744918,
			0.4784701678661044, -0.14514233862723117, 0.47476409029651834, -0.15684087019944576, 0.4707720325915104, -0.16844492669611003, 0.4664963994173695, -0.17994751826749406,
			0.46193976625564337, -0.1913417161825449, 0.45710487785176535, -0.20262065700249493, 0.45199464656172167, -0.21377754671514104, 0.44661215059775766, -0.22480566482730327,
			0.4409606321741775, -0.23569836841299882, 0.43504349555435573, -0.24644909611489202, 0.42886430500013606, -0.25705137209661083, 0.42242678262485356, -0.2674988099435486,
			0.4157348061512726, -0.2777851165098011, 0.40879240657579186, -0.28790409570892267, 0.40160376574032247, -0.2978496522462167, 0.39417321381330317, -0.3076157952903134,
			0.3865052266813685, -0.31719664208182274, 0.3786044232532423, -0.3265864214768884, 0.37047556267747955, -0.33577947742350917, 0.3621235414757335, -0.3447702723685334,
			0.3535533905932738, -0.35355339059327373, 0.34477027236853347, -0.36212354147573345, 0.33577947742350917, -0.37047556267747955, 0.3265864214768884, -0.37860442325324223,
			0.31719664208182274, -0.3865052266813685, 0.3076157952903134, -0.3941732138133031, 0.29784965224621673, -0.4016037657403224, 0.28790409570892267, -0.40879240657579186,
			0.27778511650980114, -0.4157348061512726, 0.26749880994354863, -0.4224267826248535, 0.25705137209661083, -0.42886430500013606, 0.24644909611489205, -0.4350434955543557,
			0.2356983684129989, -0.44096063217417747, 0.2248056648273033, -0.44661215059775766, 0.2137775467151411, -0.45199464656172167, 0.20262065700249493, -0.45710487785176535,
			0.19134171618254492, -0.46193976625564337, 0.17994751826749414, -0.4664963994173694, 0.16844492669611003, -0.4707720325915104, 0.1568408701994458, -0.47476409029651834,
			0.14514233862723117, -0.47847016786610447, 0.1333563787374492, -0.4818880328977199, 0.12149008995163199, -0.485015626597272, 0.10955062007843488, -0.4878510650192643,
			0.09754516100806417, -0.4903926402016152, 0.08548094438015068, -0.4926388211944706, 0.07336523722768087, -0.4945882549823905, 0.06120533759960814, -0.496239767299355,
			0.049008570164780385, -0.4975923633360984, 0.03678228179983373, -0.4986452283393451, 0.024533837163709063, -0.4993977281025862, 0.012270614261456132, -0.4998494093481021
	};

	float32_t *pS1, *pS2, *pbuff;                  /* Temporary pointers for input buffer and pState buffer */
	uint32_t i;                                    /* Loop counter */

	/* pS1 initialized to pState */
	pS1 = pState;

	/* pS2 initialized to pState+N-1, so that it points to the end of the state buffer */
	pS2 = pState + (N - 1U);

	/* pbuff initialized to input buffer */
	pbuff = pInlineBuffer;


	/* Initializing the loop counter to N/2 >> 2 for loop unrolling by 4 */
	i = Nby2 >> 2U;

	/* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
	 ** a second loop below computes the remaining 1 to 3 samples. */
	do
	{
		/* Re-ordering of even and odd elements */
		/* pState[i] =  pInlineBuffer[2*i] */
		*pS1++ = *pbuff++;
		/* pState[N-i-1] = pInlineBuffer[2*i+1] */
		*pS2-- = *pbuff++;

		*pS1++ = *pbuff++;
		*pS2-- = *pbuff++;

		*pS1++ = *pbuff++;
		*pS2-- = *pbuff++;

		*pS1++ = *pbuff++;
		*pS2-- = *pbuff++;

		/* Decrement loop counter */
		i--;
	} while (i > 0U);

	/* pbuff initialized to input buffer */
	pbuff = pInlineBuffer;

	/* pS1 initialized to pState */
	pS1 = pState;

	/* Initializing the loop counter to N/4 instead of N for loop unrolling */
	i = N >> 2U;

	/* Processing with loop unrolling 4 times as N is always multiple of 4.
	 * Compute 4 outputs at a time */
	do
	{
		/* Writing the re-ordered output back to inplace input buffer */
		*pbuff++ = *pS1++;
		*pbuff++ = *pS1++;
		*pbuff++ = *pS1++;
		*pbuff++ = *pS1++;

		/* Decrement the loop counter */
		i--;
	} while (i > 0U);


	/* ---------------------------------------------------------
	 *     Step2: Calculate RFFT for N-point input
	 * ---------------------------------------------------------- */
	/* pInlineBuffer is real input of length N , pState is the complex output of length 2N */
	arm_rfft_fast_f32 (pRfft, pInlineBuffer, pState, 0);

	/*----------------------------------------------------------------------
	 *  Step3: Multiply the FFT output with the weights.
	 *----------------------------------------------------------------------*/
	arm_cmplx_mult_cmplx_f32 (pState, Weights_64, pState, N);

	// Take only the real values and normalize
	pbuff = pInlineBuffer;
	pS1 = pState;
	for(int i = 0; i<N; i++) {
		pInlineBuffer[i] = pState[2*i] * normalize * 2;
	}
	for(int i = 0; i<13; i++) {
		mfcc_out[i] = pInlineBuffer[i];
	}

}
