#!/usr/bin/env python3

import subprocess as sp
import sys
import json
import argparse


MYSH = "./42sh"
TCSH = "/bin/tcsh"


class Parser:
    def __init__(self):
        self.parser = argparse.ArgumentParser(prog="Minishell2_tester")
        self.parser.add_argument("-f", "--file", help="File to test", required=True)
        self.parser.add_argument(
            "-v",
            "--verbose",
            help="Verbose mode",
            action=argparse.BooleanOptionalAction,
            default=False,
        )

    def parse_args(self) -> dict:
        return {k: v for k, v in self.parser.parse_args()._get_kwargs()}


class Tests:
    tests: list[dict] = []
    verbose: bool = False

    def __init__(self, args: dict):
        try:
            with open(args["file"], "r") as f:
                tests = json.loads(f.read())
                if "tests" in tests.keys():
                    self.tests = tests["tests"]
                    self.verbose = args["verbose"]
                else:
                    print("No tests found", file=sys.stderr)
                    sys.exit(1)
        except FileNotFoundError:
            print("File not found", file=sys.stderr)
            sys.exit(1)

    def _runTest(self, shell: str, run: list[str]) -> tuple[str, str]:
        try:
            proc = sp.Popen([shell], stdin=sp.PIPE, stdout=sp.PIPE, stderr=sp.PIPE)

            if proc.stdin == None:
                print("Can't start test process", file=sys.stderr)
                sys.exit(1)

            for command in run:
                proc.stdin.write(command.encode())
                proc.stdin.write(b"\n")
            proc.stdin.close()

            if proc.stdout != None and proc.stderr != None:
                return (proc.stdout.read().decode(), proc.stderr.read().decode())

            print("Can't read from test process", file=sys.stderr)
            sys.exit(1)
        except FileNotFoundError:
            print(f"[{shell}] not found", file=sys.stderr)
            sys.exit(1)

    def _printTestSuccess(
        self,
        name: str,
        run: str,
        candidate: tuple[str, str],
        reference: tuple[str, str],
    ):
        print(f"[✅] Test passed: {name}")
        if self.verbose:
            print(f"command: [{run}]")
            print(
                f"{MYSH}:",
                f"stdout: [{repr(candidate[0])}]",
                f"stderr: [{repr(candidate[1])}]",
                sep="\n",
                end="\n",
            )
            print(
                f"{TCSH}:",
                f"stdout: [{repr(reference[0])}]",
                f"stderr: [{repr(reference[1])}]",
                sep="\n",
                end="\n\n",
            )

    def _printTestFailed(
        self,
        name: str,
        run: str,
        candidate: tuple[str, str],
        reference: tuple[str, str],
    ):
        print(f"[❌] Test failed: {name}")
        print(f"command: [{run}]")
        print(
            f"Candidate:",
            f"stdout: [{repr(candidate[0])}]",
            f"stderr: [{repr(candidate[1])}]",
            sep="\n",
            end="\n\n",
        )
        print(
            f"Reference:",
            f"stdout: [{repr(reference[0])}]",
            f"stderr: [{repr(reference[1])}]",
            sep="\n",
            end="\n\n",
        )

    def run(self):
        failed_count = 0

        for test in self.tests:
            try:
                name = test["name"]
                run = test["run"]

                candidate = self._runTest(MYSH, run)
                reference = self._runTest(TCSH, run)

                if candidate != reference:
                    failed_count += 1
                    self._printTestFailed(name, run, candidate, reference)
                else:
                    self._printTestSuccess(name, run, candidate, reference)

            except KeyError:
                print("Test file syntax error", file=sys.stderr)
                sys.exit(1)

        print(f"\n{failed_count} tests failed out of {len(self.tests)}")


def main():
    args = Parser().parse_args()
    tests = Tests(args)
    tests.run()


if __name__ == "__main__":
    main()
