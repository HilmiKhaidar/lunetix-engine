#!/usr/bin/env python3

import os
import sys
import subprocess
import glob
from pathlib import Path

def generate_patch(src_dir, output_file, commit_range="HEAD~1..HEAD"):
    """Generate a patch file from git commits."""
    try:
        cmd = ['git', 'format-patch', '--stdout', commit_range]
        result = subprocess.run(cmd, cwd=src_dir, capture_output=True, text=True)
        
        if result.returncode == 0 and result.stdout:
            with open(output_file, 'w') as f:
                f.write(result.stdout)
            print(f"✓ Generated patch: {output_file}")
            return True
        else:
            print(f"✗ Failed to generate patch: {result.stderr}")
            return False
    except Exception as e:
        print(f"✗ Exception generating patch: {e}")
        return False

def list_modified_files(src_dir):
    """List modified files in the git repository."""
    try:
        cmd = ['git', 'status', '--porcelain']
        result = subprocess.run(cmd, cwd=src_dir, capture_output=True, text=True)
        
        if result.returncode == 0:
            modified_files = []
            for line in result.stdout.strip().split('\n'):
                if line:
                    status = line[:2]
                    filename = line[3:]
                    modified_files.append((status, filename))
            return modified_files
        else:
            return []
    except Exception:
        return []

def main():
    script_dir = Path(__file__).parent
    src_dir = script_dir / '../../src'
    patches_dir = script_dir / '../patches'
    
    if not src_dir.exists():
        print("Source directory not found")
        return 1
    
    patches_dir.mkdir(exist_ok=True)
    
    # List modified files
    modified_files = list_modified_files(src_dir)
    if modified_files:
        print("Modified files:")
        for status, filename in modified_files:
            print(f"  {status} {filename}")
        print()
    
    # Generate patches for recent commits
    patch_files = []
    
    # Check if there are any commits
    try:
        result = subprocess.run(['git', 'log', '--oneline', '-n', '10'], 
                              cwd=src_dir, capture_output=True, text=True)
        if result.returncode == 0 and result.stdout:
            commits = result.stdout.strip().split('\n')
            print(f"Recent commits ({len(commits)}):")
            for i, commit in enumerate(commits[:5]):
                print(f"  {i+1}. {commit}")
            print()
            
            # Generate patch for each Lunetix-related commit
            for i, commit in enumerate(commits):
                if 'lunetix' in commit.lower() or 'branding' in commit.lower():
                    commit_hash = commit.split()[0]
                    patch_file = patches_dir / f"lunetix-{commit_hash}.patch"
                    if generate_patch(src_dir, patch_file, f"{commit_hash}~1..{commit_hash}"):
                        patch_files.append(patch_file)
    except Exception as e:
        print(f"Error checking commits: {e}")
    
    if patch_files:
        print(f"\nGenerated {len(patch_files)} patch files:")
        for patch_file in patch_files:
            print(f"  - {patch_file.name}")
    else:
        print("No patches generated")
    
    return 0

if __name__ == '__main__':
    sys.exit(main())