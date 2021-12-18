function addRow(obj) {
    let table = document.querySelector("table");
    let temp = document.querySelector("#temp");
    let d = temp.content.querySelector("#tday");
    let e = temp.content.querySelector("#teo");
    let s = temp.content.querySelector("#tsub");
    let i = temp.content.querySelector("#ttime");
    let y = temp.content.querySelector("#ttype");
    d.textContent = obj.day;
    e.textContent = obj.eo;
    s.textContent = obj.sub;
    i.textContent = obj.time;
    y.textContent = obj.type;
    let tr = temp.content.cloneNode(true);
    table.append(tr);
}
function send(event){
    event.preventDefault();
    let day = document.querySelector("#day").value;
    let eo = document.querySelector("#eo").value;
    let sub = document.querySelector("#sub").value;
    let time = document.querySelector("#time").value;
    let type = document.querySelector("#type").value;
    let locstor = window.localStorage;
    locstor.setItem(id.toString(), JSON.stringify({day: day, eo: eo, sub: sub, time: time, type: type}));
    addRow({day, eo, sub, time, type});
    id++;
}
document.onkeydown = function (event) {
    if(event.which === 13) send(event);
}

let id = 0
window.addEventListener('load', function (e) {
    let locstor = window.localStorage;
    let i = 0;
    let next;
    while ((next = locstor.getItem(i.toString())) != null) {
        let mblast = JSON.parse(next);
        addRow(mblast);
        i++;
        id++;
    }
    document.querySelector('#send').onclick = function(event){
        event.preventDefault();
        let day = document.querySelector("#day").value;
        let eo = document.querySelector("#eo").value;
        let sub = document.querySelector("#sub").value;
        let time = document.querySelector("#time").value;
        let type = document.querySelector("#type").value;
        let locstor = window.localStorage;
        locstor.setItem(id.toString(), JSON.stringify({day: day, eo: eo, sub: sub, time: time, type: type}));
        addRow({day, eo, sub, time, type});
        id++;
    }

    document.querySelector('#delall').onclick = function (event) {
        event.preventDefault();
        let table = document.querySelector("table");
        for (let j = 0; j < id; j++) {
            table.deleteRow(id - j);
            window.localStorage.removeItem(j.toString())
        }
        id = 0;
    }
    document.querySelector('#delast').onclick = function (event) {
        event.preventDefault();
        let table = document.querySelector("table");
        if (window.localStorage.length > 0) {
            table.deleteRow(id);
            window.localStorage.removeItem((id - 1).toString());
            id--;
        }
    }
    // document.querySelector('#send').addEventListener('keydown', function(e) {
    //     if (e.keyCode === 13) {
    //         alert("!")
    //     }
    // });
}, false)

