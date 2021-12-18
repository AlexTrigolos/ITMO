// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
import * as vscode from 'vscode';
import * as path from 'path'; // для чтения файла и их путей
import * as util from 'util'; // для использования promisify
import * as inspector from 'inspector'; // для подключения инспектора

// this method is called when your extension is activated
// your extension is activated the very first time the command is executed
export function activate(context: vscode.ExtensionContext) {
	
	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	// The command has been defined in the package.json file
	// Now provide the implementation of the command with registerCommand
	// The commandId parameter must match the command field in package.json
	let disposable = vscode.commands.registerCommand('testlab5.helloWorld', async () => {
		// The code you place here will be executed every time your command is executed
		// Display a message box to the user
	inspector.open(); // открываем инспектора
	const session = new inspector.Session(); // получаем новую сессию из инспектора
	session.connect(); // запускаем новое соединение

	// для обшения с методом пост (<any> используем потому что post перегружен, для возможности использовать любой из них)
	const post = <any>util.promisify(session.post).bind(session);
	await post("Debugger.enable"); // активация дебагера
	await post("Runtime.enable"); // активация запуска
		vscode.window.showInformationMessage('Hello World from testlab5!');
	});

	context.subscriptions.push(disposable);
}

// this method is called when your extension is deactivated
export function deactivate() {}
