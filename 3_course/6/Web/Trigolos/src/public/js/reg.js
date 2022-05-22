const origin = window.location.origin;
async function exit() {
  event.preventDefault();
  await fetch(`${origin}/auth/signout`, {
    method: 'POST',
    body: JSON.stringify({}),
    headers: {'Content-Type': 'application/json'},
  }).then(async (response) => {
    let res = await response.text();
    if (JSON.parse(res).status === "OK") {
      fetch(`${origin}/second`, {
        method: 'POST',
        body: JSON.stringify({name: ''}),
        headers: {'Content-Type': 'application/json'},
      }).then((responses) => {
        return responses
      }).catch(err => console.log(err));
    }
    return response.json();
  }).catch(err => console.log(err));
  location.reload();
}
window.addEventListener('load', async function (e) {
  document.querySelector('#login').onclick = async function (event) {
    event.preventDefault();
    let value = document.querySelector('#log').value;
    let password = document.querySelector('#pass').value;
    await fetch(`${origin}/auth/signin`, {
      method: 'POST',
      body: JSON.stringify({
        "formFields": [
          {
            "id": "email",
            "value": value
          },
          {
            "id": "password",
            "value": password
          }
        ]
      }),
      headers: { 'Content-Type': 'application/json' },
    }).then(async (response) => {
      let res = await response.text();
      if(JSON.parse(res).status === "OK") {
        await fetch(`${origin}/second`, {
          method: 'POST',
          body: JSON.stringify({name: value}),
          headers: {
            'Content-Type': 'application/json',
          },
        }).then((responses) => {
          return responses.json();
        }).catch(err => alert(err));
      }
    }).catch(err => alert(err));
    location.reload();
  };
});
