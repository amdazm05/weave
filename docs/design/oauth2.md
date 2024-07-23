## OAuth2
"The OAuth 2.0 authorization framework enables a third-party application to obtain limited access to an HTTP service, either on behalf of a resource owner by orchestrating an approval interaction between the resource owner and the HTTP service, or by allowing the third-party application to obtain access on its own behalf."

Roles : 
- Resource Owner :
An entity capable of granting access to a protected resource.When the resource owner is a person, it is referred to as an end-user.
- Resource Server:
The server hosting the protected resources, capable of accepting and responding to protected resource requests using access tokens.

- Client :
An application making protected resource requests on behalf of the resource owner and with its authorization.  The term "client" does not imply any particular implementation characteristics (e.g.,whether the application executes on a server, a desktop, or other devices).

- Authorization Server:
The server issuing access tokens to the client after successfully authenticating the resource owner and obtaining authorization.

```

     +--------+                               +---------------+
     |        |--(A)- Authorization Request ->|   Resource    |
     |        |                               |     Owner     |
     |        |<-(B)-- Authorization Grant ---|               |
     |        |                               +---------------+
     |        |
     |        |                               +---------------+
     |        |--(C)-- Authorization Grant -->| Authorization |
     | Client |                               |     Server    |
     |        |<-(D)----- Access Token -------|               |
     |        |                               +---------------+
     |        |
     |        |                               +---------------+
     |        |--(E)----- Access Token ------>|    Resource   |
     |        |                               |     Server    |
     |        |<-(F)--- Protected Resource ---|               |
     +--------+                               +---------------+
```

## References
- https://discord.com/developers/docs/topics/oauth2
- https://datatracker.ietf.org/doc/html/rfc6749#section-1.1