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
        self.parser.add_argument(
            "-f", "--file", help="File to test", required=True)
        self.parser.add_argument(
            "-v",
            "--verbose",
            help="Verbose mode",
            action=argparse.BooleanOptionalAction,
            default=False,
        )
        self.parser.add_argument(
            "-ci",
            "--github-ci",
            help="Github CI mode",
            action=argparse.BooleanOptionalAction,
            default=False,
        )

    def parse_args(self) -> dict:
        return {k: v for k, v in self.parser.parse_args()._get_kwargs()}


class Tests:
    tests: list[dict] = []
    verbose: bool = False
    ci_mode: bool = False
    failed: bool = False

    def __init__(self, args: dict):
        try:
            with open(args["file"], "r") as f:
                tests = json.loads(f.read())
                if "tests" in tests.keys():
                    self.tests = tests["tests"]
                    self.verbose = args["verbose"]
                    self.ci_mode = args["github_ci"]
                else:
                    self._printAnnotation("No tests found", file=sys.stderr)
                    sys.exit(1)
        except FileNotFoundError:
            self._printAnnotation("File not found", file=sys.stderr)
            sys.exit(1)

    def _printAnnotation(self, message: str, test_name: str = "", file=sys.stdout):
        if self.ci_mode:
            print(
                f"::error title={'{'+test_name+'}'}:: Test failed", end="", file=file)
        print(message, file=file)

    def _runTest(self, shell: str, test_name: str, run: list[str]) -> tuple[str, str]:
        try:
            proc = sp.Popen([shell], stdin=sp.PIPE,
                            stdout=sp.PIPE, stderr=sp.PIPE)

            if proc.stdin == None:
                self._printAnnotation(
                    "Can't start test process", test_name=test_name, file=sys.stderr
                )
                sys.exit(1)

            for command in run:
                proc.stdin.write(command.encode())
                proc.stdin.write(b"\n")
            proc.stdin.close()

            if proc.stdout != None and proc.stderr != None:
                return (proc.stdout.read().decode(), proc.stderr.read().decode())

            self._printAnnotation(
                "Can't read from test process", test_name=test_name, file=sys.stderr
            )
            sys.exit(1)
        except FileNotFoundError:
            self._printAnnotation(
                f"[{shell}] not found", test_name=test_name, file=sys.stderr
            )
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
        self.failed = True
        self._printAnnotation(f"[❌] Test failed: {name}", test_name=name)
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

                candidate = self._runTest(MYSH, name, run)
                reference = self._runTest(TCSH, name, run)

                if candidate != reference:
                    failed_count += 1
                    self._printTestFailed(name, run, candidate, reference)
                else:
                    self._printTestSuccess(name, run, candidate, reference)

            except KeyError:
                print("Test file syntax error", file=sys.stderr)
                sys.exit(1)

        print(f"\n{failed_count} tests failed out of {len(self.tests)}")
        if self.failed:
            sys.exit(1)


def main():
    args = Parser().parse_args()
    tests = Tests(args)
    tests.run()


if __name__ == "__main__":
    main()
