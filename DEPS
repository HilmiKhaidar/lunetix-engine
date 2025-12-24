vars = {
  'chromium_git': 'https://chromium.googlesource.com',
  'lunetix_version': '1.0.0',
  'checkout_nacl': False,
  'checkout_android': False,
  'checkout_ios': False,
  'checkout_mac': False,
  'checkout_linux': False,
  'checkout_win': True,
}

deps = {
  'src': {
    'url': Var('chromium_git') + '/chromium/src.git@main',
    'condition': 'True',
  },
  'src/lunetix': {
    'url': 'file://' + Var('lunetix_root') + '/lunetix',
    'condition': 'True',
  },
}

hooks = [
  {
    'name': 'lunetix_patches',
    'pattern': '.',
    'action': ['python3', 'src/lunetix/tools/apply_patches.py'],
  },
  {
    'name': 'lunetix_branding',
    'pattern': '.',
    'action': ['python3', 'src/lunetix/tools/setup_branding.py'],
  },
]