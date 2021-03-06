const requestURL = "https://jsonplaceholder.typicode.com/todos"
const locstor = window.localStorage;
let deleted

class Task {
    constructor(id, task, checked) {
        this.id = id;
        this.title = task;
        this.completed = checked;
    }
}

function change(allTasks, at) {
    for (let i = 0; i < allTasks.length / 2; i++) {
        let one = at.children[i].innerHTML;
        let uno = at.children[i].children[1].children[0].checked;
        let duo = at.children[allTasks.length - i - 1].children[1].children[0].checked;
        at.children[i].innerHTML = at.children[allTasks.length - i - 1].innerHTML;
        at.children[allTasks.length - i - 1].innerHTML = one;
        if (uno !== duo) {
            at.children[i].classList.toggle("del_task")
            at.children[i].children[1].children[0].checked = duo
            at.children[allTasks.length - i - 1].classList.toggle("del_task")
            at.children[allTasks.length - i - 1].children[1].children[0].checked = uno
        } else {
            at.children[i].children[1].children[0].checked = duo
            at.children[allTasks.length - i - 1].children[1].children[0].checked = uno
        }
    }
}

function sortUp() {
    let at = document.querySelector("#all_tasks");
    let allTasks = JSON.parse(locstor.getItem("tasks"));
    if (at.children[0].children[0].textContent.split(".")[0] < at.children[allTasks.length - 1].children[0].textContent.split(".")[0]) {
        change(allTasks, at);
    }
}

function sortDown() {
    let at = document.querySelector("#all_tasks");
    let allTasks = JSON.parse(locstor.getItem("tasks"));
    if (at.children[0].children[0].textContent.split(".")[0] > at.children[allTasks.length - 1].children[0].textContent.split(".")[0]) {
        change(allTasks, at);
    }
}

function countText(text){
    let count = 0;
    for (let i = 0; i < deleted.length; i++) {
        if (deleted[i] < text) {
            count++;
        }
    }
    return count;
}

function check(elem) {
    let content = elem.parentNode.parentNode.childNodes[1];
    let text = elem.parentNode.parentNode.childNodes[1].textContent;
    let textNum = text.split(".")[0]
    let allTasks = JSON.parse(locstor.getItem("tasks"))
    let count = countText(textNum);

    allTasks[textNum - 1 - count]['completed'] = allTasks[textNum - 1 - count]['completed'] !== true;
    locstor.setItem("tasks", JSON.stringify(allTasks));
    content.classList.toggle("del_text");
    content.parentNode.classList.toggle("del_task");
}

function deleteTask(elem) {
    let delTextNum = elem.parentNode.parentNode.children[0].textContent.split(".")[0];
    let allTasks = JSON.parse(locstor.getItem("tasks"));
    let count = countText(delTextNum);
    allTasks.splice(delTextNum - 1 - count, 1);
    elem.parentNode.parentNode.parentNode.removeChild(elem.parentNode.parentNode);
    deleted.push(delTextNum - 1);
    if (allTasks.length === 0) {
        locstor.removeItem("tasks");
    } else {
        locstor.setItem("tasks", JSON.stringify(allTasks));
    }
}

function addNewTask(elem) {
    let allTasks = JSON.parse(locstor.getItem("tasks"));
    let newTask = document.querySelector("#new_task").value;
    let cnt = new Task(allTasks.length, newTask, false);
    allTasks.push(cnt);
    locstor.setItem("tasks", JSON.stringify(allTasks));
    addTask(cnt.id + 1 + deleted.length, cnt);
}

function addTask(ID, obj) {
    let at = document.querySelector("#all_tasks");
    let temp = document.querySelector("#temp");
    let tt = temp.content.querySelector("#task_text");
    let cb = temp.content.querySelector("#checkbox");
    tt.textContent = ID.toString() + ". " + obj['title'];
    cb.textContent = obj['completed'];
    let d = temp.content.cloneNode(true);
    at.append(d);
    if (cb.textContent === "true") {
        return ID;
    }
    return -1;
}

function checkCompleted(completed){
    let at = document.querySelector("#all_tasks");
    for (let j = 0; j < completed.length; j++) {
        at.children[completed[j] - 1].classList.toggle("del_task");
        at.children[completed[j] - 1].children[0].classList.toggle("del_text");
        at.children[completed[j] - 1].children[1].children[0].checked = true;
    }
}

function haveTasks() {
    // locstor.removeItem("tasks")
    let completed = []
    let next = locstor.getItem("tasks");
    let mblast = JSON.parse(next);
    let i = 0;
    while (mblast[i] !== undefined) {
        let cb = addTask(i + 1, mblast[i])
        if (cb !== -1) {
            completed.push(cb);
        }
        i++;
    }
    checkCompleted(completed);
}

async function okResp(response){
    let tasks = []
    let completed = []
    let data = await response.json();
    let ID = -100;
    for (let i = 0; i < data.length; i++) {
        if (ID === -100) {
            ID = data[i].id - 1;
        }
        tasks.push(new Task(data[i]['id'], data[i]['title'], data[i]['completed']));
        let cb = addTask(data[i]['id'] - ID, data[i])
        if (cb !== -1) {
            completed.push(cb);
        }
    }
    checkCompleted(completed)
    locstor.setItem("tasks", JSON.stringify(tasks));
}

async function haventTasks() {
    let uId = Math.floor(Math.random() * 10) + 1;
    let response = await fetch(requestURL + "?userId=" + uId.toString());
    if (response.ok) {
        await okResp(response);
    } else {
        let body = document.querySelector("body");
        body.children[1].children[3].innerHTML = "<div>??? ??????-???? ?????????? ???? ??????</div>";
    }
}

window.addEventListener('load', async function (e) {
    let tasks = JSON.parse(locstor.getItem("tasks"));
    deleted = []
    if (tasks != null) {
        haveTasks();
    } else {
        await haventTasks();
    }
    document.querySelector('#send').onclick = function (event) {
        event.preventDefault();
        addNewTask(this);
    }
    const preloader = document.getElementById("page_preloader");
    if (!preloader.classList.contains('done')) {
        preloader.classList.add("done");
    }
})
