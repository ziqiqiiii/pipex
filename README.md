# pipex

Minimal Unix pipeline recreation in C. This project emulates shell piping and redirection:

Mandatory: `./pipex infile "cmd1 args" "cmd2 args" outfile` executes `cmd1 < infile | cmd2 > outfile`.

Bonus: `./pipex_bonus` supports an arbitrary number of commands and a heredoc mode:
`./pipex_bonus here_doc LIMITER "cmd1" "cmd2" ... outfile`.

## 1. Purpose
Implement low-level inter-process communication and I/O redirection using only allowed C/POSIX system calls. It reinforces understanding of:
- `fork`, `pipe`, `dup2`, `execve`, `waitpid`
- File descriptor lifecycle and resource safety
- PATH resolution and command argument parsing
- Handling heredoc input without a shell

## 2. Features
Mandatory version:
- Two-command pipeline connecting stdout of first to stdin of second
- Infile read and outfile creation/truncation
- Basic error handling (argument count, missing file, command lookup)

Bonus version:
- N-command pipelines (dynamically determined by argc)
- Heredoc support (`here_doc LIMITER`) with interactive input until LIMITER line
- Outfile opened in append mode for heredoc variant
- Cleanup of temporary heredoc file

Common implementation details:
- Custom PATH search: splits `$PATH`, appends '/', tests each candidate with `access()`
- Command parsing: first word is executable; remainder passed as arguments
- Memory management for all allocated 2D arrays (`envp`, command paths)
- Custom thin wrappers (`ft_open`, `ft_pipe`, `ft_fork`, `ft_close`) for clarity and unified error messaging

## 3. Build
```bash
# Mandatory
make

# Bonus
make bonus

# Clean / full rebuild
make fclean && make
```

## 4. Usage Examples
Mandatory:
```bash
./pipex infile "ls -l" "wc -l" outfile
./pipex input.txt "grep error" "sort" result.txt
```

Bonus multi-command:
```bash
./pipex_bonus infile "cat" "grep TODO" "wc -l" out.txt
```

Bonus heredoc:
```bash
./pipex_bonus here_doc LIMITER "grep pattern" "wc -l" out.txt
# Type lines, finish with a line exactly matching LIMITER
```

## 5. Architecture Overview
Core struct `t_data` (see `includes/pipex.h` / `pipex_bonus.h`): holds file descriptors, command count, PATH directories, resolved executable paths, heredoc flag (bonus), and current pipe.

Main flow (mandatory):
1. Validate argc and input file existence.
2. Build PATH directory list from environment.
3. Resolve each command into an absolute executable path.
4. Open infile (read) and outfile (write/truncate).
5. Create pipe; fork first child (redirect infile->stdin, pipe write->stdout); fork second child (redirect pipe read->stdin, outfile->stdout).
6. Parent closes pipe ends and waits for children.
7. Free memory and close descriptors.

Bonus adds:
- Heredoc pre-phase writing input into `.here_doc_tmp`, replacing infile.
- Loop that spawns middle children; each iteration wires previous pipe read end as stdin and new pipe write end as stdout.
- Final child writes to outfile (APPEND if heredoc, else TRUNC).

## 6. Key System Calls
| Call   | Purpose |
|--------|---------|
| `open` | Open/create infile/outfile and heredoc tmp |
| `pipe` | Create unidirectional communication channel |
| `fork` | Spawn child processes for each command |
| `dup2` | Rewire stdin/stdout to file or pipe ends |
| `execve` | Replace child image with target executable |
| `waitpid` | Synchronize parent with children termination |
| `access` | Check executable existence in PATH search |
| `unlink` | Remove heredoc temporary file (bonus) |

## 7. Testing and Validation
---
For quick validation:
```bash
make && ./pipex infile "echo hello" "wc -c" out.txt && cat out.txt
```
