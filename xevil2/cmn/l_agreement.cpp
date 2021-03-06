/*
 *  XEvil(TM) Copyright (C) 1994,1999  Steve Hardt and Michael Judge
 *  
 *  The file, license.txt, distributed along with this source code contains
 *  the license agreement for the XEvil source code and executable.
 *  If you do not have this file, obtain a copy from 
 *  http://www.xevil.com/docs/license.txt
 * 
 *  http://www.xevil.com
 *  satan@xevil.com
 */

// "l_agreement.cpp"  

#if X11
#ifndef NO_PRAGMAS
#pragma implementation "l_agreement.h"
#endif
#endif

#include "stdafx.h"
#include "utils.h"
#include "l_agreement.h"



Line::Line(const char **textRet,const char *text) {
  const char *p = text;

#if 0
  // First eat beginning WS.  Assuming no tabs.
  while (*p && *p == ' ') {
    p++;
  }
#endif

  start = p;

  // Adding words
  Boolean hitEOL;
  while (1) {
    hitEOL = False;

    // End of string.
    if (!*p) {
      length = (p - start);
      *textRet = p;
      break;
    }
    if (*p == '\n') {
      length = (p - start);
      // Eat the '\n' character.
      *textRet = p + 1;
      hitEOL = True;
      break;
    }

    // Search for end of next word.
    const char* wordP = p;
    // Eat leading word WS.
    while (*wordP && *wordP == ' ') {
      wordP++;
    }
    while (*wordP && *wordP != ' ' && *wordP != '\n') {
      wordP++;
    }
    if (wordP - start > textColumns) {
      // This is the only word on the line.
      // Will have to break word in two.
      if (p == start) {
        length = textColumns;
        *textRet = start + textColumns;
        break;
      }

      // Break at the end of the previous word.
      length = p - start;
      *textRet = p;
      break;
    }

    // Add word to current line.
    p = wordP;
  }

  // Eat trailing WS.
  if (!hitEOL) {
    while (**textRet && **textRet == ' ') {
      (*textRet)++;
    }
  }
}



char* Line::alloc_text() {
  char* ret = new char[length + 1];
  assert(ret);
  for (int n = 0; n < length; n++) {
    ret[n] = *(start + n);
  }
  ret[length] = '\0';
  return ret;
}



int Line::textColumns = 65;



Page::Page(const char **textRet,const char *text) {
  const char *p = text;
  // If textRet is NULL, put everything in one page.
  // Ignore textRows all together.
  while (*p && (!textRet || lines.length() < textRows)) {
    Line* line = new Line(&p,p);
    lines.add(line);
  }
  if (textRet) {
    *textRet = p;
  }
  else {
    assert(!(*p));
  }
}



Page::~Page() {
  for (int n = 0; n < lines.length(); n++) {
    delete (Line*)lines.get(n);
  }
}



int Page::textRows = 25;



Boolean LAgreement::commLineAccepted = False;



const char *LAgreement::get_text() {
  return 
  "XEvil(TM) copyright(C) 1994,1999 Steve Hardt and Michael Judge\n"
  "http://www.xevil.com\n"
  "satan@xevil.com\n"
  "\n"
  "\n"
  "\n"
  "--> SHAREWARE <--\n"
  "\n"
  "XEvil and the XEvil source code are shareware.\n"
  "Send a $20 check or money order made out to \"Steve Hardt\":\n"
  "XEvil \n"
  "P.O. Box 391530\n"
  "Mountain View, CA 94039-1530\n"
  "\n"
  "See the SHAREWARE and PAYMENT sections for details.\n"
  "\n"
  "\n"
  "\n"
  "If you wish to do something disallowed by this agreement, contact "
  "the authors.  We can probably work something out.\n"
  "\n"
  "XEVIL(TM) LICENSE AGREEMENT\n"
  "-----------------------------\n"
  "SCOPE\n"
  "This license agreement covers XEvil version \"2.0 beta 7\" and all subsequent "
  "versions of XEvil starting with \"2.\", e.g. \"XEvil 2.0 beta 8\", \"XEvil 2.0\", "
  "\"XEvil 2.51\".  It does not cover XEvil version \"2.0 beta 6\" or any earlier "
  "version and does not cover any version starting with \"3.\" or greater.\n"
  "\n"
  "\n"
  "TERMINOLOGY\n"
  "\"Authors\" means Steve Hardt and Michael Judge.\n"
  "\n"
  "\"XEvil License Agreement Dialog\" means the window that appears immediately "
  "when XEvil is run and disappears before the game starts.  It displays the "
  "entire text of this license agreement.\n"
  "\n"
  "\"Source Code\" means all C/C++ files, graphics files, sound files, makefiles, "
  "project files, and any other files needed to build the final executable.\n"
  "\n"
  "\n"
  "SHAREWARE\n"
  "XEvil executables and the XEvil source code are shareware.  To support future "
  "XEvil development, purchase an XEvil shareware registration for $20.\n"
  "\n"
  "The $20 shareware registration gives the registered person the right to run "
  "XEvil on one platform and gives that one person the right to use the XEvil "
  "source code for personal use.  Registration for additional platforms cost $10 "
  "each.  For example, if you want to run XEvil as a server on your FreeBSD "
  "machine and connect to it with XEvil running as a client on a Windows 95 "
  "machine, you should pay for two platforms, $30.  There is one exception.  "
  "Windows 95, Windows 98, and Windows NT are different platforms, but payment "
  "for one is considered payment for all three.\n"
  "\n"
  "The XEvil source code itself is shareware.  If you wish to use the XEvil "
  "source code for your own use, including reading the code for personal "
  "education, you should pay the shareware fee.\n"
  "\n"
  "We distribute the full implementation of XEvil, with all features enabled, "
  "and distribute the complete source code.  We do not retain any way of forcing "
  "you to register XEvil.  Instead, we hope you will get more than $20 worth of "
  "benefit out of XEvil and will show us your appreciation.  Invest in future "
  "XEvil features, graphics, sound, ports, bug fixes, etc. by paying the "
  "registration fee.\n"
  "\n"
  "\n"
  "PAYMENT\n"
  "Send check or money order to: \n"
  "XEvil \n"
  "P.O. Box 391530\n"
  "Mountain View, CA 94039-1530\n"
  "\n"
  "Make the check out to \"Steve Hardt\" and <IMPORTANT> write the version number "
  "and operating system names in the memo portion of the check </IMPORTANT>.  "
  "For example, \"XEvil 2.0 Red Hat Linux\", \"XEvil 2.0 Windows 98\", or "
  "\"XEvil 2.0 Windows 95, Windows NT, Solaris\".  Although you only have to pay "
  "for at most one of Windows 95, Windows 98, and Windows NT, please tell us "
  "specifically which platforms you use.  This information helps us decide how "
  "to allocate our development and testing resources.\n"
  "\n"
  "\n"
  "DISTRIBUTION\n"
  "Executable:\n"
  "The XEvil executable for any platform may be freely distributed provided this "
  "license agreement in its original and complete form is distributed along with "
  "the executable.\n"
  " \n"
  "The executable may be bundled as part of another product (e.g. shareware CD or "
  "operating system) provided this license agreement in its original and complete "
  "form is distributed along with the executable.  The bundled product must be "
  "set up so that the user sees the XEvil License Agreement Dialog every time "
  "XEvil is run.  This bundling is allowed only with the understanding that "
  "end-users should still pay the XEvil authors the shareware fee as described in "
  "this agreement.  Purchase of another product that bundles XEvil does not "
  "imply purchase of an XEvil shareware registration.\n"
  "\n"
  "Source code:\n"
  "The XEvil source code may be freely distributed provided this "
  "license agreement in its original and complete form is distributed along with "
  "the source.  As with the executable, bundling of the XEvil source code is "
  "allowed with the understanding that end-users should still pay the XEvil "
  "authors the shareware fee.\n"
  "\n"
  "\n"
  "INSTALLATION\n"
  "If XEvil is installed on a machine used by multiple users or installed on a "
  "network, it must be set up so that users see the XEvil license agreement "
  "dialog every time XEvil runs.  XEvil may only be configured to run without "
  "displaying the XEvil License Agreement Dialog if it is installed such that "
  "only one person uses it and if that person has paid the XEvil shareware "
  "registration fee.\n"
  "\n"
  "\n"
  "MODIFYING THE EXECUTABLE OR SOURCE CODE\n"
  "You may modify the XEvil executable and source code and make builds of XEvil "
  "for other platforms.  Distribution of such executables is allowed only if the "
  "original XEvil License Agreement Dialog with the original text is displayed "
  "immediately when the program runs.  You may add additional dialogs or "
  "introductory screens, but the original XEvil License Agreement Dialog must "
  "appear first.\n"
  "\n"
  "Distribution of modified XEvil source code is permitted provided this license "
  "agreement is distributed along with the source code and provided the entire "
  "XEvil source code base is included.\n"
  "\n"
  "If you distribute a modified XEvil executable it must inform the user in some "
  "way that it is not an original executable distributed by the authors.  If you "
  "distribute modified XEvil source code, you must include a file in the top "
  "level directory of the distribution that gives a brief description of the "
  "changes.  This file must have a descriptive name, such as \"changes.txt\".  "
  "You may not distribute modified XEvil source code or a modified executable "
  "with the intention of convincing others that it is the original source code "
  "or executable.\n"
  "\n"
  "You may not distribute a portion of the XEvil source code less than the entire "
  "distribution, e.g. just the XEvil networking code.  In particular, every "
  "distributed version of the XEvil source code must include all code to display "
  "the XEvil License Agreement Dialog immediately when XEvil runs.\n"
  "\n"
  "A version of the XEvil source code that differs from the original XEvil source "
  "code only in minor changes to the build script files made for the sole purpose "
  "of compiling XEvil on some specific machine and platform is considered the "
  "original source code for the purposes of this agreement.  An executable built "
  "from the original XEvil source code is considered an original executable.\n"
  "\n"
  "\n"
  "COPYRIGHT OF MODIFICATIONS\n"
  "The authors own the full copyright for all modified versions of XEvil.  If "
  "requested by the authors, you must send the authors copies of all source code "
  "and executables for the modified version(s).  This includes all graphics, "
  "sound, and other media used in the modified version of XEvil.  By distributing "
  "a modified version of XEvil, you are granting the authors copyright for your "
  "modifications.\n"
  "\n"
  "\n"
  "NO WARRANTY\n"
  "This software is provided 'as is', without any express or implied warranty, "
  "including, but not limited to, the implied warranties of merchantability and "
  "fitness for a particular purpose.  The entire risk as to the quality and "
  "performance of the program is with you.  Should the program prove defective, "
  "you assume the cost of all necessary servicing, repair or correction.\n"
  "\n"
  "In no event will the authors be liable to you for damages, including any "
  "general, special, incidental, or consequential damages arising out of the use "
  "or inability to use the program (including but not limited to loss of data or "
  "data being rendered inaccurate or losses sustained by you or third parties or "
  "a failure of the program to operate with any other programs), even if the "
  "authors have been advised of the possibility of such damages.\n"
  "\n"
  "\n"
  "EXCEPTIONS\n"
  "If you wish to do something with XEvil disallowed by this agreement, contact "
  "the authors.  We are reasonable people and we can probably work something out.\n"
  "\n"
  "\n"
  "XEVIL CREDITS:\n"
  "   Send email to satan@xevil.com\n"
  "\n"
  "Design and Architecture:\n"
  "   Steve Hardt\n"
  "Windows Front End:\n"
  "   Michael Judge\n"
  "   Steve Hardt\n"
  "UNIX Front End:\n"
  "   Steve Hardt\n"
  "Cross Platform Code:\n"
  "   Steve Hardt\n"
  "Artwork:\n"
  "   Comrade.Cid\n"
  "   Steve Hardt\n"
  "   Michael Judge\n"
  "   frankwu.com\n"
  "   Anthony Davis\n"
  "   Matthew Dey\n"
  "   Michael Davidson\n"
  "   Peter Arsoff\n"
  "   Brian Nelson\n"
  "Music:\n"
  "   Ann Greyson\n"
  "   Michael Cummings\n"
  "   D.J. Litany\n"
  "Sound:\n"
  "   Michael Judge\n"
  "\n"
  "\n"
  "Windows 95, Windows 98, and Windows NT are registered trademarks of Microsoft "
  "Corporation.\n"
  "Red Hat is a registered trademark of Red Hat Software, Inc.\n"
  "Solaris is a registered trademark of Sun Microsystems.\n"
  "FreeBSD is a registered trademark of FreeBSD, Inc. and Walnut Creek CDROM.\n"
  "\n"
  "last modified 1/10/99\n"
  ;
}


