# scripts to compile the mapping.

import os
import sys
import argparse
import subprocess

def checkPath (path):
    if not os.path.exists (path):
        print '[Integrate-Error] Path', path, 'not exists.'
        return False
    else:
        return True

def checkFile (fname):
    if not os.path.isfile (fname):
        print '[Integrate-Error] File', fname, 'not exist.'
        return False
    else:
        return True

def cat (src, dstWrite):
    with open (src, 'r') as rFile:
        for line in rFile:
            dstWrite.write (line)

def createMap (mapConnectPath, fwFunPath, hwInstrPath, outFileName):
    assert checkPath (mapConnectPath)
    assert checkPath (fwFunPath)
    assert checkPath (hwInstrPath)

    def mapOne (funName, instrName, interfaceName, outWrite):
        # check function definition is in the directory
        funEntryFile  = '%s/%s_entry.smt2' % (fwFunPath, funName)
        funExitFile   = '%s/%s_exit.smt2' % (fwFunPath, funName)
        # check instruction predicate is in the directory
        instrFile     = '%s/%s.smt2' % (hwInstrPath, instrName)
        # check interface clauses is in the directory
        interfaceFile = '%s/%s.smt2' % (mapConnectPath, interfaceName)

        assert checkFile (funEntryFile)
        assert checkFile (funExitFile)
        assert checkFile (instrFile)
        assert checkFile (interfaceFile)

        # Start parsing files
        # Entry -> Interface --> stripped Instr --> Exit
        cat (funEntryFile, outWrite)
        cat (interfaceFile, outWrite)
        
        instrPred = ''
        with open (instrFile, 'r') as instrRead:
            for line in instrRead:
                instrPred = line
                break
        instrPredSet = instrPred.split (')')
        instrPred = instrPredSet[0] + ')\n'
        instrPredSet = instrPred.split ('(')
        instrPred = '\t\t(' + instrPredSet[1] 
        outWrite.write (instrPred)

        cat (funExitFile, outWrite)

    outWrite = open (outFileName, 'w')

    mmioFun = 'HW_REG_WRITE_chr'
    # fe00
    mapOne (mmioFun, 'sha_fe00', 'map_fe00', outWrite)
    # fd00
    mapOne (mmioFun, 'rsa_fd00', 'map_fd00', outWrite)

    outWrite.close()


if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument ("mapConnectPath", type = str,
						 help = "path for map connection")
	parser.add_argument ("fwFunPath", type = str,
						 help = "path for firmware function")
	parser.add_argument ("hwInstrPath", type = str,
						 help = "path for hardware instruction")
	parser.add_argument ("outFileName", type = str,
						 help = "output file for mapping clauses")
	args = parser.parse_args()

	createMap (args.mapConnectPath, args.fwFunPath, args.hwInstrPath, args.outFileName)