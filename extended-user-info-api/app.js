require('dotenv').config();
const request = require('request');
const express = require('express');

var port = process.env.PORT || 1187;
var botToken = process.env.BOT_TOKEN;

const app = express();
app.use(express.json());

app.listen(port, () => {
    console.log("Server Listening on PORT:", port);
});

app.get("/*", (a, response) => {

    const options = {
        url: 'https://discord.com/api/v10/users/' + a.params[0],
        headers: {
            'Authorization': 'Bot ' + botToken
        }
    };

    function callback(error, aresponse, body) {
        if (!error && aresponse.statusCode == 200) {
            var preuser = JSON.parse(body);
            var user = {
                "id": preuser.id,
                "global_name": preuser.global_name,
                "public_flags": preuser.public_flags,
                "flags": preuser.flags,
                "accent_color": preuser.accent_color,
                "avatar_decoration_url": "https://cdn.discordapp.com/avatar-decorations/" + preuser.id + "/" + preuser.avatar_decoration + ".png",
                "avatar_decoration": preuser.avatar_decoration,
                "banner_url": "https://cdn.discordapp.com/banners/" + preuser.id + "/" + preuser.banner + ".png",
                "banner": preuser.banner,
                "banner_color": preuser.banner_color,
            };
            response.send(user);
        }
        else {
            response.send(aresponse.statusCode)
        }
    }

    request(options, callback);


});
