target directories
internalPluginsDirectory
	"return the directory for the internal plugins sources"
	|fd|
	fd := self coreVMDirectory / 'intplugins'.
	fd ensureCreateDirectory.
	^fd