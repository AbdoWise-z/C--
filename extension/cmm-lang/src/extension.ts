import * as vscode from 'vscode';
import * as os from 'os';
import * as path from 'path';
import * as fs from 'fs';
import { exec } from 'child_process';
import * as util from 'util';
import { parseTableText } from './SymbolTableParser';

const execAsync = util.promisify(exec);

interface Entry { line: number; message: string; }

async function runCmmCompiler(
	command: string,
  ): Promise<{
	raw: string;
	warnings: Entry[];
	errors: Entry[];
  }> {
	const cmd = `${command}`;
	const { stdout, stderr } = await execAsync(cmd);
	const all = stdout + stderr;
  
	const warnRe  = /^\[Warn\]\s+(\d+)\s+(.+)$/i;
	const errorRe = /^\[Error\]\s+(\d+)\s+(.+)$/i;
  
	const warnings: Entry[] = [];
	const errors:   Entry[] = [];
  
	for (const line of all.split(/\r?\n/)) {
	  let m = warnRe.exec(line);
	  if (m) {
		warnings.push({ line: parseInt(m[1], 10), message: m[2].trim() });
		continue;
	  }
	  m = errorRe.exec(line);
	  if (m) {
		errors.push({ line: parseInt(m[1], 10), message: m[2].trim() });
	  }
	}
  
	return { raw: all, warnings, errors };
}

async function loadFileText(filePath: string): Promise<string> {
	const ws = vscode.workspace.workspaceFolders;
	if (!ws) throw new Error('No workspace open.');

	return fs.promises.readFile(filePath, 'utf-8');
}



export function createReadOnlyCodePanel(
	viewId: string,
	title: string,
	languageId: string,
	code: string,
	column: vscode.ViewColumn = vscode.ViewColumn.One
): vscode.WebviewPanel {
	// Create the panel
	const panel = vscode.window.createWebviewPanel(
		viewId,   // internal identifier
		title,    // shown in the editor tab
		column,   // column to show in
		{
		enableScripts: false,       // no scripts needed
		enableFindWidget: true,     // allow searching
		retainContextWhenHidden: true
		}
	);

	// Escape HTML special chars for safe embedding
	const escapeHtml = (str: string) =>
		str.replace(/&/g, '&amp;')
		.replace(/</g, '&lt;')
		.replace(/>/g, '&gt;');

	const highlighted = escapeHtml(code);

	// Set the HTML content
	panel.webview.html = `<!DOCTYPE html>
	<html lang="en">
	<head>
		<meta charset="UTF-8" />
		<style>
		body {
			margin: 0;
			padding: 1rem;
			background: #1e1e1e;
			color: #d4d4d4;
			font-family: Consolas, 'Courier New', monospace;
		}
		h1 {
			margin: 0 0 1rem;
			font-size: 1.4rem;
			color: #ffffff;
		}
		pre {
			background: #252526;
			padding: 1rem;
			border-radius: 4px;
			overflow: auto;
		}
		/* simple token coloring */
		.keyword { color: #569cd6; }
		.string  { color: #ce9178; }
		.comment { color: #6a9955; font-style: italic; }
		</style>
	</head>
	<body>
		<h1>${title}</h1>
		<pre><code>${highlighted}</code></pre>
	</body>
	</html>`;

	return panel;
}


function getWebviewContent(headers: string[], rows: string[][]): string {
	const headerRow = headers.map(h => `<th>${h}</th>`).join('');
	const bodyRows = rows.map(r => {
	  const cells = r.map(c => `<td>${c}</td>`).join('');
	  return `<tr>${cells}</tr>`;
	}).join('');
  
	return `
	  <!DOCTYPE html>
	  <html lang="en">
	  <head>
		<style>
		  :root {
			--bg-color: #1e1e1e;
			--header-bg: #252526;
			--row-odd: #2a2a2a;
			--row-even: #232323;
			--row-hover: #3a3d41;
			--border-color: #3c3c3c;
			--text-color: #cccccc;
			--header-text: #ffffff;
		  }
		  body {
			margin: 0;
			padding: 0.5rem;
			background: var(--bg-color);
			color: var(--text-color);
			font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Helvetica, Arial, sans-serif;
		  }
		  h2 {
			margin: 0 0 0.5rem 0;
			color: var(--header-text);
		  }
		  .table-container {
			height: calc(100vh - 2rem); /* fill viewport minus padding and header */
			overflow-y: auto;
			border: 1px solid var(--border-color);
			border-radius: 4px;
		  }
		  table {
			width: 100%;
			border-collapse: collapse;
		  }
		  thead th {
			position: sticky;
			top: 0;
			background: var(--header-bg);
			color: var(--header-text);
			padding: 0.75rem;
			text-align: left;
			border-bottom: 1px solid var(--border-color);
			z-index: 1;
		  }
		  tbody tr:nth-child(odd) {
			background: var(--row-odd);
		  }
		  tbody tr:nth-child(even) {
			background: var(--row-even);
		  }
		  tbody tr:hover {
			background: var(--row-hover);
		  }
		  td {
			padding: 0.6rem;
			border-bottom: 1px solid var(--border-color);
			vertical-align: top;
		  }
		</style>
	  </head>
	  <body>
		<h2>Symbol Table</h2>
		<div class="table-container">
		  <table>
			<thead>
			  <tr>${headerRow}</tr>
			</thead>
			<tbody>
			  ${bodyRows}
			</tbody>
		  </table>
		</div>
	  </body>
	  </html>
	`;
}
  
  
export function activate(context: vscode.ExtensionContext) {

	// context.subscriptions.push(
	// 	vscode.commands.registerCommand('cmm-lang.helloWorld', () => {
	// 		vscode.window.showInformationMessage('Hello World from HelloWorld!');
	// 	})
	// );

	// Run Command
	context.subscriptions.push(
		vscode.commands.registerCommand('cmm-lang.runFile', (fileUri?: vscode.Uri) => {
			runInTerminal('run', fileUri);
		})
	);

	// Debug Command
	context.subscriptions.push(
		vscode.commands.registerCommand('cmm-lang.debugFile', (fileUri?: vscode.Uri) => {
			runInTerminal('debug', fileUri);
		})
	);

	// Build Command
	context.subscriptions.push(
		vscode.commands.registerCommand('cmm-lang.buildFile', async (fileUri?: vscode.Uri) => {
			const editor = vscode.window.activeTextEditor;
			const filePath = fileUri?.fsPath || editor?.document.uri.fsPath;
			if (!filePath) {
				vscode.window.showErrorMessage('No file selected!');
				return;
			}

			const tmpDir = os.tmpdir();
			const symFile   = path.join(tmpDir, `sym_table-${Date.now()}.txt`);
			const quadsFile = path.join(tmpDir, `quad_table-${Date.now()}.txt`);

			const command = `Cmm --file "${filePath}" --I "${getParentFolder(vscode.Uri.file(filePath)).fsPath}" --symbols "${symFile}" --quads "${quadsFile}"`;
			const { raw, warnings, errors } = await runCmmCompiler(command);

			const panel = vscode.window.createWebviewPanel(
				'SymbolTable',
				'Symbols View',
				vscode.ViewColumn.One,
				{}
			);

			try {
				const tableText = await loadFileText(symFile);
				const { headers, rows } = parseTableText(tableText);
				panel.webview.html = getWebviewContent(headers, rows);
			} catch (error) {
				vscode.window.showErrorMessage(`Failed to load symbols: ${error}`);
				panel.dispose();
			}

			try {
				const quads = await loadFileText(quadsFile);
				createReadOnlyCodePanel(
					'cmm-quads.snippetView',
					'Generated Quads',
					'quads',
					quads,
					vscode.ViewColumn.Two
				);
			} catch (error) {
				vscode.window.showErrorMessage(`Failed to load quads: ${error}`);
			}
		})
	);

	const tmpDir    = os.tmpdir();
	const symFile   = path.join(tmpDir, `sym_table-${Date.now()}.txt`);
	const quadsFile = path.join(tmpDir, `quad_table-${Date.now()}.txt`);

	// async side effect
	const collection = vscode.languages.createDiagnosticCollection('cmm');
	context.subscriptions.push(collection);
	const disposable = vscode.workspace.onDidChangeTextDocument(async (event) => {
		if (event.document.languageId !== 'cmm') return;

		const filePath  = event.document.fileName;
		
		const command = `Cmm --file "${filePath}" --I "${getParentFolder(vscode.Uri.file(filePath)).fsPath}" --symbols "${symFile}" --quads "${quadsFile}"`;

		const { raw, warnings, errors } = await runCmmCompiler(command);
		console.log(raw);

		const diagnostics: vscode.Diagnostic[] = [];

		for (const entry of [...warnings]) {
			const range = new vscode.Range(entry.line - 1, 0, entry.line - 1, Number.MAX_SAFE_INTEGER);
			const severity = vscode.DiagnosticSeverity.Warning;
			diagnostics.push(new vscode.Diagnostic(range, entry.message, severity));
		}

		for (const entry of [...errors]) {
			const range = new vscode.Range(entry.line - 1, 0, entry.line - 1, Number.MAX_SAFE_INTEGER);
			const severity = vscode.DiagnosticSeverity.Error;
			diagnostics.push(new vscode.Diagnostic(range, entry.message, severity));
		}

		collection.set(event.document.uri, diagnostics);
	});

	context.subscriptions.push(disposable);
}

function getParentFolder(fileUri: vscode.Uri): vscode.Uri {
    return fileUri.with({ path: vscode.Uri.joinPath(fileUri, '..').path });
}

function runInTerminal(action: 'run' | 'debug', fileUri?: vscode.Uri) {
	// Use the editor's current document if not provided
	const editor = vscode.window.activeTextEditor;
	const filePath = fileUri?.fsPath || editor?.document.uri.fsPath;
	if (!filePath) {
		vscode.window.showErrorMessage('No file selected!');
		return;
	}

	let command = '';
	if (action === 'run')   command = `Cmm --file "${filePath}" --I "${getParentFolder(vscode.Uri.file(filePath)).fsPath}"`;
	if (action === 'debug') command = `Cmm --file "${filePath}" --I "${getParentFolder(vscode.Uri.file(filePath)).fsPath}" --debug`;
	// Use a VS Code terminal:
	const terminal = vscode.window.createTerminal('CMM');
	terminal.show();
	terminal.sendText(command);
}