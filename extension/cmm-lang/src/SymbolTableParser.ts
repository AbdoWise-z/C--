// Helper: Parse the text file into headers and rows,
// correctly handling '|' inside double-quoted strings.
export function parseTableText(text: string): { headers: string[], rows: string[][] } {
    const lines = text
      .trim()
      .split('\n')
      .filter(line => line.trim());
  
    // A small state-machine to split a single line
    function splitRow(line: string): string[] {
      const cells: string[] = [];
      let current = '';
      let inString = false;
  
      for (let i = 0; i < line.length; i++) {
        const ch = line[i];
  
        if (ch === '"' && line[i - 1] !== '\\') {
          // toggle inString when we see an unescaped quote
          inString = !inString;
          current += ch;
        } else if (ch === '|' && !inString) {
          // delimiter outside of string
          cells.push(current.trim());
          current = '';
        } else {
          current += ch;
        }
      }
      // push last cell
      cells.push(current.trim());
      // remove any leading/trailing empty cells (from leading/trailing pipes)
      return cells.filter(cell => cell.length > 0);
    }
  
    // Parse header (first line)
    const headers = splitRow(lines[0]);
  
    // Parse data rows
    const rows = lines.slice(1).map(splitRow);
  
    return { headers, rows };
  }
  