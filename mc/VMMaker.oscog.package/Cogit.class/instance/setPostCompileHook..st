jit - api
setPostCompileHook: aFunction
	<api>
	<var: #aFunction declareC: #'void (*aFunction)(CogMethod *, void *)'>
	postCompileHook := aFunction