#----------------------------------------------------------------------
# $Id: NCISoapCgi.py,v 1.1.1.1 2002-06-03 16:51:20 jholmes Exp $
#
# Stub for SOAP interface to CDR from Cancer.gov.
#
# $Log: not supported by cvs2svn $
#----------------------------------------------------------------------
import os, sys, re

class NCISoapCgi:

    def __init__( self ):
        self.ini_done = 1
        self.BLOCK_SIZE = 1024

        
    #----------------------------------------------------------------------
    # Send an XML SOAP message back to the client.
    #----------------------------------------------------------------------
    def SendMessage(self, msg):
        print """\
    Content-type: text/xml

    <?xml                  version = "1.0"
                          encoding = "UTF-8"?>
    <env:Envelope        xmlns:env = "http://schemas.xmlsoap.org/soap/envelope/"
                 env:encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/">
     <env:Body>
    %s
     </env:Body>
    </env:Envelope>
    """ % msg
        sys.exit(0)

    #----------------------------------------------------------------------
    # Send an error message back to the client.
    #----------------------------------------------------------------------
    def SendErrorMessage(self, msg, code = "Server", details = None):
        #print "got here sem1"

        # Start the fault element
        fault = """\
      <env:Fault>
       <faultcode>env:%s</faultcode>
       <faultstring>%s</faultstring>
    """ % (code, msg)

        # Add option details if specified.
        if details:
            fault += """
       <detail>
        <details>%s</details>
       </detail>
    """ % details

        # Finish up and send it off.
        self.sendMessage("""\
       %s
      </env:Fault>
    """ % fault)

    #----------------------------------------------------------------------
    # Gather in the client's message.
    #----------------------------------------------------------------------
    def ReadRequest( self ):
        requestMethod = os.getenv("REQUEST_METHOD")
        if not requestMethod:
            self.SendErrorMessage("Request method not specified")
        if requestMethod != "POST":
            self.SendErrorMessage("Request method should be POST; was %s" % requestMethod, "Client")
        contentLengthString = os.getenv("CONTENT_LENGTH")
        if not contentLengthString:
            self.SendErrorMessage("Content length not specified")
        try:
            contentLength = int(contentLengthString)
        except:
            self.SendErrorMessage("Invalid content length: %s" % contentLengthString)
        if contentLength < 1:
            self.SendErrorMessage("Invalid content length: %s" % contentLengthString)
        try:
            request = ""
            tl = 0
            while ( tl < contentLength - self.BLOCK_SIZE ):
                request += sys.stdin.read( self.BLOCK_SIZE )
                tl += self.BLOCK_SIZE
            request += sys.stdin.read( contentLength - tl )
        except:
            self.SendErrorMessage("Failure reading message")
            
        return request

#        "<env:Body>\n"
#		"%s\n"
#		"</env:Body>\n"
		
    def ExtractBody( self, soap_msg ):
        prog = re.compile( "<env:Body>(.*)</env:Body>", re.S )
        mg = prog.search( soap_msg )
        #print "MG ", mg
        if ( mg ):
            result = mg.group(1)
        else:
            result = ""
        return result


# Main is used mainly for testing
def Main():
    soap_test = NCISoapCgi()
    r = soap_test.ExtractBody( "<env:Body>\n<xy>\nzzy\n</env:Body>" )
    print "result is ", r

# determine if we are invoked standalone, if so invoke testing mode
if __name__ == "__main__":
    Main()
