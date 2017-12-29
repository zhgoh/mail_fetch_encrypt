Create a C++ console application to retrieve items in specific Gmail mailbox
(filtered by specified period of time) and store them in the same folder in encrypted form
(algorithm should be chosen by yourself).

Parameters are: mailbox name, mailbox password, start of the retrieval period,
end of the retrieval period.

You need to use official API provided by Google, no IMAP/POP3.


NOTE:

To use this project, certain files are needed but I am providing it with the project for ease of testing.

1. roots.pem       - Provided by google API
2. secrets.json    - Create and download a new credentials from https://console.developers.google.com/
3. rsa_privkey.pem - Generated with openssl genrsa -out rsa_privkey.pem 1024
4. rsa_pubkey.pem  - Generated with openssl rsa -pubout -in rsa_privkey.pem -out rsa_pubkey.pem

This application will download mails from GMail, encrypt the mails and store it into a folder named messages.
You can use the same application to decrypt the messages.
