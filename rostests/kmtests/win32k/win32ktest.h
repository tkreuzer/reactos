/*
 * PROJECT:         ReactOS kernel-mode tests
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         win32k Test Suite Loader Application
 * PROGRAMMER:      Timo Kreuzer
 */

#ifndef _KMTESTS_H_
#define _KMTESTS_H_

extern PCSTR ErrorFileAndLine;

#ifndef KMT_STRINGIZE
#define KMT_STRINGIZE(x) #x
#endif /* !defined KMT_STRINGIZE */

#define location(file, line)                    do { ErrorFileAndLine = file ":" KMT_STRINGIZE(line); } while (0)
#define error_value(Error, value)               do { location(__FILE__, __LINE__); Error = value; } while (0)
#define error(Error)                            error_value(Error, GetLastError())
#define error_goto(Error, label)                do { error(Error); goto label; } while (0)
#define error_value_goto(Error, value, label)   do { error_value(Error, value); goto label; } while (0)


#endif /* !defined _KMTESTS_H_ */
