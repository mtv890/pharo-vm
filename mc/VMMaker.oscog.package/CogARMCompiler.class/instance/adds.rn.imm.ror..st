ARM convenience instructions
adds: destReg rn: srcReg imm: immediate ror: rot
"return an ADDS destReg, srcReg, immediat ROR rot instruction"

	^self type: 1 op: 4 set: 1 rn: srcReg rd: destReg shifterOperand: (rot <<8 bitOr: immediate)