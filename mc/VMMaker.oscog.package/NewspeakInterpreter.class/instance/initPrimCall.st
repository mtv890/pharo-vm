primitive support
initPrimCall
	"Selt the failure code/success flag in preparation for calling a primitve.
	 If primfailCode is non-zero a primitive has failed.  If primFailCode is greater
	 than one then its value indicates the reason for failure."
	<inline: true>
	primFailCode := 0