class initialization
ensureNotifiedAtStartup
	"Alien needs to be notified at system startup to clear the LoadedLibraries table
	and otherwise sanitise Aliens with dangling pointers."
	self ~~ Alien ifTrue: [^self].
	Smalltalk addToStartUpList: self after: Delay