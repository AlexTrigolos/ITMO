const Toast = {
    init() {
        this.hideTimeout = null;
        this.el = document.createElement("div");
        this.el.className = "toast";
        document.body.appendChild(this.el);
    },

    show(name, message) {
        clearTimeout(this.hideTimeout);
        this.el.textContent = name + ": " + message;
        this.el.className = "toast toast--visible";

        this.hideTimeout = setTimeout(() => {
            this.el.classList.remove("toast--visible");
        }, 3000);
    }
};

document.addEventListener("DOMContentLoaded", () => Toast.init());