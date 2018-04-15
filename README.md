### Mail Retrieve App
Create a C++ console application to retrieve items in specific Gmail mailbox
(filtered by specified period of time) and store them in the same folder in encrypted form
(algorithm should be chosen by yourself).

Parameters are: mailbox name, mailbox password, start of the retrieval period,
end of the retrieval period.

You need to use official API provided by Google, no IMAP/POP3.


## Running the app
Download mails and save as encrypted format:

    folder: inbox/draft/sent/etc
    start: YYYY-MM-DD
    end:   YYYY-MM-DD
    $> ./app ./secrets.json [folder] [start date] [end date] 

Decrypt mails:

    $> ./app
    


## Note:
To use this project, certain files are needed but I am providing it with the project for ease of testing.

1. roots.pem       - Provided by google API
2. secrets.json    - Create and download a new credentials from https://console.developers.google.com/
3. rsa_privkey.pem - Generated with openssl genrsa -out rsa_privkey.pem 1024
4. rsa_pubkey.pem  - Generated with openssl rsa -pubout -in rsa_privkey.pem -out rsa_pubkey.pem

This application will download mails from GMail, encrypt the mails and store it into a folder named messages.
You can use the same application to decrypt the messages.

## Generating OpenSSL asymmetric keys
    # Generate private key
    $ openssl genrsa -out rsa_privkey.pem 1024
    
    # Generate public key from private key
    $ openssl rsa -pubout -in rsa_privkey.pem -out rsa_pubkey.pem
     
## OpenSSL EVP_SEAL functions
I took the reference code from this [stack overflow link](https://stackoverflow.com/questions/9406840/rsa-encrypt-decrypt)

## Issues with Google API
- Missing function
- Function Signature mismatch

Some things to not is Google API generator for c++ is broken.
The first issue is commonly in some of the files, (message.cc, message_part.cc)
Example of a missing function.

Fix: Just write the missing functions, the functions are quite trival
and just access Storage.

    const MessagePart Message::get_payload() const
    {
        const Json::Value &storage = Storage("payload");
        return client::JsonValueToCppValueHelper<MessagePart>(storage);
    }

Another issue is that there is some function signature mismatched caused by the generator, 
see this issue
https://github.com/google/google-api-cpp-client/issues/41

Fix: (gmail_service.cc).
Note: line 2 uses string instead of StringPiece for the generated code which does not
override the parent class properly.

    util::Status UsersResource_GetProfileMethod::AppendVariable(
                const string &variable_name,
                const client::UriTemplateConfig &config,
                string *target)
        {
